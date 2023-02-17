dtrace:::BEGIN
{
    printf("We are starting to protect ...\n");
}

dtrace:::END
{
    printf("We are done protecting ...\n");
}

/* Necessary for printing out a unicode string. */
struct ustr{uint16_t buffer[256];};
/* A set of bytes to use to "null out" the handle's value. */
uint8_t null[8];

/*
 * A typedef so we can write HANDLE and remind ourselves
 * what we are really working with.
 */
typedef uintptr_t *HANDLE;

/*
 * A variable that we can use to indicate whether we are
 * going to make debugging output.
 */
inline int debug_mode = 1;

/*
 * Why are we monitoring NtCreateFile? Not something
 * more reasonable? https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-openfile
 * Documentation for NtCreateFile: https://learn.microsoft.com/en-us/windows/win32/api/winternl/nf-winternl-ntcreatefile
 */
syscall::NtCreateFile:entry
/*
 * Only do the following for the dangerous process. 
 */
/ strstr(execname, "XFilTr8") != "" /
{
    self->phandle = (HANDLE*)0;
    self->fname_buffer = (uint16_t*)NULL;
    self->fname_buffer_len = 0;

    /* Gather the information required to determine whether to disrupt
     * this particular invocation of the NtCreateFile function.
     */
    this->attr = (POBJECT_ATTRIBUTES)
        copyin(arg2, sizeof(OBJECT_ATTRIBUTES));

    if (this->attr->ObjectName) {
        this->objectName = (PUNICODE_STRING)
            copyin((uintptr_t)this->attr->ObjectName,
                    sizeof(UNICODE_STRING));

        this->fname_buffer = (uint16_t*)
            copyin((uintptr_t)this->objectName->Buffer,
                    this->objectName->Length);
        this->fname_buffer_len = this->objectName->Length;

        /*
         * Be very careful here -- this may mess up further
         * processing or even fail to work at all!
         * And, for some unknown reason, if you put this code deeper
         * in a conditional, it fails to work. I. Have. No. Idea.
         */
        printf("Process %s PID %d opened file %*ws \n",
            execname,
            pid,
            this->fname_buffer_len / 2,
            ((struct ustr*)this->fname_buffer)->buffer);
    }

    if (this->fname_buffer_len != 0) {
        self->phandle = (HANDLE*)arg0;
        this->lphandle = (HANDLE)copyin((uintptr_t)self->phandle, sizeof(HANDLE));
        /*
         * Yes, this is quite confusing: self->phandle is a pointer to a handle.
         * We cannot read the target of that handle unless/until we read it into
         * kernel memory. 
         * phandle -------> [   HANDLE VALUE   ]
         *                  <- sizeof(HANDLE) ->
         * So, let's read in sizeof(HANDLE) bytes from the target of phandle (i.e.)
         *                  ^^^^^^^^^^^^^^^^^^^^^
         * into kernel space (use copyin). That gives us a pointer to the memory
         * that we read in. In other words, 
         * lphandle ------> [   HANDLE VALUE   ]
         *                  <- sizeof(HANDLE) ->
         * So, we have to dereference lphandle read the actual value. Whew. So. Many.
         * Dereferences.
         */
        this->handlev = (uintptr_t)(*this->lphandle);

        if (debug_mode == 1) {

            printf("(%s) Before invoking NtCreateFile, the handle's value is %x.\n", execname, this->handlev);
        }
    }
}

syscall::NtCreateFile:return
/self->phandle != (HANDLE*)0 /
{
    this->lphandle = (HANDLE)copyin((uintptr_t)self->phandle, sizeof(HANDLE));
    this->handlev = (uintptr_t)(*this->lphandle);
    if (debug_mode == 1) {
        printf("(%s) In response to an NtCreateFile call, the kernel assigned handle 0x%x.\n", execname, this->handlev);
    }

    copyout((void*)null, (uintptr_t)self->phandle, sizeof(null));
    
    this->lphandle = (HANDLE)copyin((uintptr_t)self->phandle, sizeof(HANDLE));
    this->handlev = (uintptr_t)(*this->lphandle);

    if (debug_mode == 1) {
        printf("(%s) After applying protection, the handle's value is 0x%x.\n", execname, this->handlev);
    }

    self->phandle = (HANDLE*)0;
}