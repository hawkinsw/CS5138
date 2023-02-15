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
int debug_mode;

/*
 * Why are we monitoring NtCreateFile? Not something
 * more reasonable? https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-openfile
 * Documentation for NtCreateFile: https://learn.microsoft.com/en-us/windows/win32/api/winternl/nf-winternl-ntcreatefile
 */
syscall::NtCreateFile:entry
/ strstr(execname, "XFilTr8") != "" /
{
    debug_mode = 1;

    self->phandle = (HANDLE*)0;
    self->fname_buffer = (uint16_t*)NULL;
    self->fname_buffer_len = 0;

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

        printf("Process %s PID %d opened file %*ws \n",
            execname,
            pid,
            this->fname_buffer_len / 2,
            ((struct ustr*)this->fname_buffer)->buffer);
    }
}