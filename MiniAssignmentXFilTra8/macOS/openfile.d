dtrace:::BEGIN
{
    printf("We are starting to protect ...\n");
}

dtrace:::END
{
    printf("We are done protecting ...\n");
}

/*
 * Look up `man 2 open` for information about the open POSIX function.
 */
syscall::read:entry 
/ strstr(execname, "XFilTr8") != "" /
{
    /*
     * In all cases, let's reset all the shared flags (just for safety).
     */
     self->inspect = 0;
     self->stopit = 0;
}

syscall::read:entry 
/*
 * Only do the following for the dangerous process. 
 */
/ strstr(execname, "XFilTr8") != "" /
{
    /*
     * Set a flag that we are going to inspect this process.
     * (see the predicates below)
     */
    self->inspect = 1;

    /*
     * Reset the flag that indicates whether we are going to be stopping
     * this process from accessing data.
     */
    self->stopit = 0;

    this->fd = arg0;
    /*
     * Drill through the data structures in the kernel to find
     * the path associated with the filehandle.
     */
    this->fp = (struct fileproc *)(curproc->p_fd.fd_ofiles[this->fd]);
    this->fg = (struct fileglob *)(this->fp->fp_glob);
    this->fg_data = this->fg->fg_data;
    this->vnode  = (struct vnode *)strip((struct vnode *)(this->fg_data),
                                          ptrauth_key_process_independent_code);
    /*
     * We only need to record the path (after all that work!)
     */
    self->path = this->vnode->v_name;

}

/*
 * We are using a series of probes with the same
 * names but different predicates instead of using
 * if statements. That's all!
 */
syscall::read:entry
/ self->inspect == 1 && self->path != NULL /
{
    /* Log the path of the file associated with this file descriptor.
     */
    printf("path? %s\n", stringof(self->path));
}

/*
 * Let's check to see whether this is the secret file that we want to
 * prevent from being read!
 */
syscall::read:entry
/ self->inspect == 1 && strstr(self->path, "secret.txt") != "" /
{
    printf("Definitely stopping this one: %s!\n", stringof(self->path));
    /*
     * If this read is from a file handle associated with the secret file,
     * let's record the other information we will need in the syscall::read:return
     * probe to do the blocking: A pointer to the buffer and its length.
     */
    self->buffer = arg1;
    self->buffer_len = arg2;
    /*
     * Finally, mark that we are interested in blocking the results of
     * this read.
     */
    self->stopit = 1;
}

syscall::read:return
/ self->inspect == 1 && self->stopit == 1 /
{
  self->stopit = 0;
  self->inspect = 0;
  self->empty = alloca(self->buffer_len);
  if (self->empty != NULL) {
    copyout(self->empty, self->buffer, self->buffer_len);
  } else {
    printf("Error: Could not allocate enough memory to overwrite the entirety of the buffer.\n");
  }
}


