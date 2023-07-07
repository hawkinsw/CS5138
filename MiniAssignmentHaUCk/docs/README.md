# The HaUCk Bank Malware

Sometimes users' desire to follow best practices backfires on them. In our case, a user has submitted a program to us for analysis. They believe that the application might have led to a compromise of their system. The user received a phone call from their bank, HaUCk Bank, and the operator needed to do some routine account checkups. The user, the bank's client, received an email with information on how to download software that would help them generate a one-time password that they could use to verify their identity with the bank and protect themselves from fraud. The operator asked them to use the HaUCk Bank Multifactor Authenticator (HBMA) to generate such a token so that the user would have peace of mind that they were talking to a legitimate bank representative. 

When our user ran the password-generator software, everything seemed normal ...

```console
$ hauck-mfa
HaUCk Bank: Securing financial freedom since 1982.
Your one-time token/MFA key is 1902. Please provide it to the customer service representative.
```

After completing the call with the bank representative, things started to get a little, well, crazy. 

As our company's premiere cybersecurity analyst, we have been given the task of determining whether or not the password generator was legitimate or malicious.

## Using External Libraries
Software developers don't write their code in a vacuum -- they work with other developers as a team and often rely on software from others. Code from others usually comes in the form of external libraries. Libraries are packages of precompiled code that can be reused to accomplish a specific task. We qualify the term *library* with *external* to distinguish libraries written by teams of developers we don't know and libraries that are written by members of our team. 

Malware writers are no different than other software engineers. Malicious hackers want to write code as easily and quickly as possible and that often requires a reliance on other people's work.

One of the first things to do when coming in contact with a piece of suspicious code is to determine whether the libraries that it uses are consistent with the job that the software purports to do. In the case of our password-generating application, it seems reasonable to expect that a random-number generator might be needed or even a piece of supporting code to perform encryption.

Just how is it possible to determine what external libraries a program uses? `ldd` is how!

### Description

`ldd` is a tool that understands the format of an executable Linux program and can determine which external libraries that program relies on to execute. In its default mode, `ldd` will list all the required external libraries for the particular program whose path is provided as the argument.

### Practice
To practice with `ldd`, let's investigate what external libraries `host` needs from the operating system to execute. 

`host` is a little command that will perform *DNS resolution* on a hostname. *DNS resolution* is the process of using the domain name system (DNS) to convert a hostname (e.g., `google.com`) into an IP address (e.g., `4.3.2.10` or `2607:f8b0:4009:803::200e`).

```console
$ ldd /usr/bin/host
```
Depending on the version of Linux operating system you are using, your output should look similar to:
```console
$ ldd /usr/bin/host
        linux-vdso.so.1 (0x00007fff4b1f8000)
        libisc-9.18.8-1-Debian.so => /lib/x86_64-linux-gnu/libisc-9.18.8-1-Debian.so (0x00007f481e800000)
        libdns-9.18.8-1-Debian.so => /lib/x86_64-linux-gnu/libdns-9.18.8-1-Debian.so (0x00007f481e400000)
        libisccfg-9.18.8-1-Debian.so => /lib/x86_64-linux-gnu/libisccfg-9.18.8-1-Debian.so (0x00007f481eea1000)
        libirs-9.18.8-1-Debian.so => /lib/x86_64-linux-gnu/libirs-9.18.8-1-Debian.so (0x00007f481ee9b000)
        libbind9-9.18.8-1-Debian.so => /lib/x86_64-linux-gnu/libbind9-9.18.8-1-Debian.so (0x00007f481ee83000)
        libidn2.so.0 => /lib/x86_64-linux-gnu/libidn2.so.0 (0x00007f481ee50000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f481e61f000)
        libuv.so.1 => /lib/x86_64-linux-gnu/libuv.so.1 (0x00007f481ee20000)
        libssl.so.3 => /lib/x86_64-linux-gnu/libssl.so.3 (0x00007f481e357000)
        libcrypto.so.3 => /lib/x86_64-linux-gnu/libcrypto.so.3 (0x00007f481de00000)
        libz.so.1 => /lib/x86_64-linux-gnu/libz.so.1 (0x00007f481ee03000)
        libjemalloc.so.2 => /lib/x86_64-linux-gnu/libjemalloc.so.2 (0x00007f481da00000)
        libjson-c.so.5 => /lib/x86_64-linux-gnu/libjson-c.so.5 (0x00007f481edee000)
        libnghttp2.so.14 => /lib/x86_64-linux-gnu/libnghttp2.so.14 (0x00007f481edbf000)
        libxml2.so.2 => /lib/x86_64-linux-gnu/libxml2.so.2 (0x00007f481d852000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f481ef0c000)
        libgssapi_krb5.so.2 => /lib/x86_64-linux-gnu/libgssapi_krb5.so.2 (0x00007f481e305000)
        libkrb5.so.3 => /lib/x86_64-linux-gnu/libkrb5.so.3 (0x00007f481dd26000)
        libmaxminddb.so.0 => /lib/x86_64-linux-gnu/libmaxminddb.so.0 (0x00007f481edb6000)
        libfstrm.so.0 => /lib/x86_64-linux-gnu/libfstrm.so.0 (0x00007f481eda9000)
        libprotobuf-c.so.1 => /lib/x86_64-linux-gnu/libprotobuf-c.so.1 (0x00007f481ed9f000)
        liblmdb.so.0 => /lib/x86_64-linux-gnu/liblmdb.so.0 (0x00007f481e2ee000)
        libns-9.18.8-1-Debian.so => /lib/x86_64-linux-gnu/libns-9.18.8-1-Debian.so (0x00007f481e2a2000)
        libunistring.so.2 => /lib/x86_64-linux-gnu/libunistring.so.2 (0x00007f481d69c000)
        libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007f481ed98000)
        libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007f481ed93000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f481d5bd000)
        libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f481d200000)
        libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f481e282000)
        libicuuc.so.71 => /lib/x86_64-linux-gnu/libicuuc.so.71 (0x00007f481d004000)
        liblzma.so.5 => /lib/x86_64-linux-gnu/liblzma.so.5 (0x00007f481dcfe000)
        libk5crypto.so.3 => /lib/x86_64-linux-gnu/libk5crypto.so.3 (0x00007f481d590000)
        libcom_err.so.2 => /lib/x86_64-linux-gnu/libcom_err.so.2 (0x00007f481e617000)
        libkrb5support.so.0 => /lib/x86_64-linux-gnu/libkrb5support.so.0 (0x00007f481dcf0000)
        libkeyutils.so.1 => /lib/x86_64-linux-gnu/libkeyutils.so.1 (0x00007f481e60e000)
        libresolv.so.2 => /lib/x86_64-linux-gnu/libresolv.so.2 (0x00007f481dcdf000)
        libicudata.so.71 => /lib/x86_64-linux-gnu/libicudata.so.71 (0x00007f481b200000)
```

Part of being a good malware analyst is an expertise with Google. Take some time and use your Google-fu to research one of the libraries above. Try to determine what kinds of functionality the library provides to software that uses it. Is the library open source? Where can you find the source code? Have there ever been vulnerabilities in that library? If so, what does that mean for software that relies on it?

### Do

Investigate what external libraries the HBMA uses and determine the functionality provided by those libraries.

<details><summary>Answer</summary>

```console
$ ldd hauck-mfa
```

```console
$ ldd hauck-mfa
        linux-vdso.so.1 (0x00007ffe09163000)
        libcurl.so.4 => /lib64/libcurl.so.4 (0x00007ff820170000)
        libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007ff81fe00000)
        libm.so.6 => /lib64/libm.so.6 (0x00007ff820090000)
        libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007ff820070000)
        libc.so.6 => /lib64/libc.so.6 (0x00007ff81fc23000)
        libnghttp2.so.14 => /lib64/libnghttp2.so.14 (0x00007ff820043000)
        libidn2.so.0 => /lib64/libidn2.so.0 (0x00007ff81fbd6000)
        libssl.so.3 => /lib64/libssl.so.3 (0x00007ff81fb33000)
        libcrypto.so.3 => /lib64/libcrypto.so.3 (0x00007ff81f600000)
        libgssapi_krb5.so.2 => /lib64/libgssapi_krb5.so.2 (0x00007ff81fadc000)
        libz.so.1 => /lib64/libz.so.1 (0x00007ff81fac2000)
        /lib64/ld-linux-x86-64.so.2 (0x00007ff82020c000)
        libunistring.so.2 => /lib64/libunistring.so.2 (0x00007ff81f448000)
        libkrb5.so.3 => /lib64/libkrb5.so.3 (0x00007ff81f36b000)
        libk5crypto.so.3 => /lib64/libk5crypto.so.3 (0x00007ff81faa9000)
        libcom_err.so.2 => /lib64/libcom_err.so.2 (0x00007ff82003a000)
        libkrb5support.so.0 => /lib64/libkrb5support.so.0 (0x00007ff81fa98000)
        libkeyutils.so.1 => /lib64/libkeyutils.so.1 (0x00007ff81fa91000)
        libresolv.so.2 => /lib64/libresolv.so.2 (0x00007ff81fa7e000)
        libselinux.so.1 => /lib64/libselinux.so.1 (0x00007ff81fa51000)
        libpcre2-8.so.0 => /lib64/libpcre2-8.so.0 (0x00007ff81f2ce000)
```

The most fascinating of the libraries required by the HBMA is [`libcurl.so.4`](https://curl.se/libcurl/), a.k.a. `libcurl`. `libcurl` is an extremely popular open-source project (it was used in the [Mars Rover](https://daniel.haxx.se/blog/2021/12/03/why-curl-is-used-everywhere-even-on-mars/)!!). The project produces libraries that makes it easy for developers to write programs that download data from the internet using the HTTP(S) protocol. Does it seem like there is a good reason for a simple program that generates a multifactor token to access the Internet? I agree ... something seems suspicious.
</details>

## System Calls

Operating systems are an amazing creation. Their power, fundamentally, is to orchestrate the execution of programs written by us so-called *application developers* and make sure that our programs are able to use all of a computer's resources. Many of the things that we want our programs to do requires access to hardware connected to a computer -- storing files requires access to a disk drive, displaying graphics on a screen requires access to a graphics card, and accessing the internet requires access to a network interface. The only problem is that there are a *ton* of different hardware resources and it would be immensely difficult if every application developer had to learn the intricacies of all those devices just to use them in their applications. The operating system is here to rescue us.

The operating system provides *abstractions* so that we can use the computer's hardware resources without having to learn the details. In order to do that, our programs need to request access to those resources in a standard way through an application programming interface (API). Application developers access this API through *system calls*. You can find a list of some of the system calls available to application developers in Windows at the [MSDN](https://learn.microsoft.com/en-us/windows/win32/api/winternl/).

As an example of how application developers use system calls, here is some code that opens a file named "myreport.docx":

```C
#include <fcntl.h>

int main() {
  int fd = open("myreport.docx", O_RDONLY);
  if (fd < 0) {
    // handle an error
    ...
  }
  // use the file.
  ...
}
```

If we had access to the source code for all the potentially malicious software that we want to investigate then we could easily determine what resources a piece of software is requesting from the operating system just like we can see that the hypothetical program above is accessing a file named "myreport.docx" on the computer's hard drive.

But that is most definitely not the case. Instead, we will have to rely on a tool that will allow us to snoop on executing programs and see what system calls they are making. 

The tool is named `strace`.

### Description

`strace` lets us analysts start the execution of a program and watch what system calls it makes. It takes a single command-line parameter -- the path to the program to monitor -- in its simplest mode of execution.

```console
$ strace /path/to/program
```

### Practice

First, open the provided file named `whereami.txt` in the `samples` directory by using a text editor (say, `mousepad`, for example). Make sure that you can see that it has the following contents:

```
At the best summer camp in all of Cincinnati!
```

`cat` is a program that allows the user to display the contents of text files on the screen from the console. Let's say that you want to display the contents of the `whereami.txt` file on the screen, you could run

```console
$ cat samples/whereami.txt
```

and you would get the following output:

```console
$ cat samples/whereami.txt
CyberSecurity summer camp at UC is really fun!
```

In order to be able to produce that output, the `cat` program must access the computer's hard drive and therefore has to use a system call. Let's use `strace` to determine the system calls that it makes when attempting to display the contents of the `samples/whereami.txt` file:

```console
$ strace /usr/bin/cat samples/whereami.txt
```

will generate a ton of output:

```
$ strace /usr/bin/cat samples/whereami.txt
execve("/usr/bin/cat", ["/usr/bin/cat", "docs/samples/whereami.txt"], 0x7ffea95a77e8 /* 67 vars */) = 0
brk(NULL)                               = 0x562dd163e000
arch_prctl(0x3001 /* ARCH_??? */, 0x7ffd4964f410) = -1 EINVAL (Invalid argument)
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f33d0c5a000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=96323, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 96323, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f33d0c42000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\320v\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=2224288, ...}, AT_EMPTY_PATH) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
mmap(NULL, 1953104, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f33d0a65000
mmap(0x7f33d0a8b000, 1400832, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x26000) = 0x7f33d0a8b000
mmap(0x7f33d0be1000, 339968, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x17c000) = 0x7f33d0be1000
mmap(0x7f33d0c34000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1ce000) = 0x7f33d0c34000
mmap(0x7f33d0c3a000, 32080, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f33d0c3a000
close(3)                                = 0
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f33d0a62000
arch_prctl(ARCH_SET_FS, 0x7f33d0a62740) = 0
set_tid_address(0x7f33d0a62a10)         = 1902312
set_robust_list(0x7f33d0a62a20, 24)     = 0
rseq(0x7f33d0a63060, 0x20, 0, 0x53053053) = 0
mprotect(0x7f33d0c34000, 16384, PROT_READ) = 0
mprotect(0x562dd03bd000, 4096, PROT_READ) = 0
mprotect(0x7f33d0c8f000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x7f33d0c42000, 96323)           = 0
getrandom("\x99\xca\x53\x12\x0b\x78\xee\x5f", 8, GRND_NONBLOCK) = 8
brk(NULL)                               = 0x562dd163e000
brk(0x562dd165f000)                     = 0x562dd165f000
openat(AT_FDCWD, "/usr/lib/locale/locale-archive", O_RDONLY|O_CLOEXEC) = 3
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=224104272, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 224104272, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f33c3400000
close(3)                                = 0
newfstatat(1, "", {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0x6), ...}, AT_EMPTY_PATH) = 0
openat(AT_FDCWD, "docs/samples/whereami.txt", O_RDONLY) = 3
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=46, ...}, AT_EMPTY_PATH) = 0
fadvise64(3, 0, 0, POSIX_FADV_SEQUENTIAL) = 0
mmap(NULL, 139264, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f33d0a40000
read(3, "At the best summer camp in all o"..., 131072) = 46
write(1, "At the best summer camp in all o"..., 46At the best summer camp in all of Cincinnati!
) = 46
read(3, "", 131072)                     = 0
munmap(0x7f33d0a40000, 139264)          = 0
close(3)                                = 0
close(1)                                = 0
close(2)                                = 0
exit_group(0)                           = ?
+++ exited with 0 +++
```

Let's focus in on two very interesting lines:

```
...
read(3, "At the best summer camp in all o"..., 131072) = 46
...
```

This line of output is describing how `strace` caught `cat` reading from a file on the hard drive using the `read` system call. The *file handle* that it is reading from is `3` and the data it read was `At the best summer camp in all ...` -- does that look familiar?

>Note: That `read` system call actually retrieved the entire contents of the file -- the output generated by `strace` cut it off to make sure that it fit nicely on the screen.

What is a file handle (a.k.a., a file descriptor) and how do we get one that we can use to access a particular file? Let's go back to the `open` system call that we saw earlier! The return value of the `open` system call is a file handle. So, that means that `strace` should have caught `cat` issuing an `open` system call and that should be logged somewhere in the output above ...

```
...
openat(AT_FDCWD, "docs/samples/whereami.txt", O_RDONLY) = 3
...
```

and there it is! First, do you see the path of the file? How awesome! 

Second, notice that the `3` in the `= 3` is the same as the `3` in the `read(3 ...)` -- that is no coincidence. The `3` file descriptor is used by system calls that want to manipulate the file opened by that particular call to the `open` system call. See how the file descriptor provides the logical link between the `open` and the `read` system calls? 

### Do

Run the HBMA using `strace` and determine if (and with that parameters does) the HBMA uses the [`connect`](https://linux.die.net/man/2/connect) system call.

<details><summary>Answer</summary>

```console
$ strace src/install/bin/hauck
execve("./src/install/bin/hauck-mfa", ["./src/install/bin/hauck-mfa"], 0x7ffd985defe0 /* 67 vars */) = 0
brk(NULL)                               = 0x81c000
arch_prctl(0x3001 /* ARCH_??? */, 0x7fff2724c670) = -1 EINVAL (Invalid argument)
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f9ee0b6e000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=96323, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 96323, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f9ee0b56000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libcurl.so.4", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=534952, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 528784, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9ee0ad4000
mprotect(0x7f9ee0adf000, 466944, PROT_NONE) = 0
mmap(0x7f9ee0adf000, 376832, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0xb000) = 0x7f9ee0adf000
mmap(0x7f9ee0b3b000, 86016, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x67000) = 0x7f9ee0b3b000
mmap(0x7f9ee0b51000, 16384, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x7c000) = 0x7f9ee0b51000
mmap(0x7f9ee0b55000, 400, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f9ee0b55000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libstdc++.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=2360128, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 2308096, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9ee0800000
mprotect(0x7f9ee089a000, 1609728, PROT_NONE) = 0
mmap(0x7f9ee089a000, 1118208, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x9a000) = 0x7f9ee089a000
mmap(0x7f9ee09ab000, 487424, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1ab000) = 0x7f9ee09ab000
mmap(0x7f9ee0a23000, 57344, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x222000) = 0x7f9ee0a23000
mmap(0x7f9ee0a31000, 10240, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f9ee0a31000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libm.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=928216, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 913680, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9ee0720000
mmap(0x7f9ee0730000, 475136, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x10000) = 0x7f9ee0730000
mmap(0x7f9ee07a4000, 368640, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x84000) = 0x7f9ee07a4000
mmap(0x7f9ee07fe000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0xdd000) = 0x7f9ee07fe000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libgcc_s.so.1", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=128536, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 127272, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9ee0ab4000
mmap(0x7f9ee0ab7000, 94208, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x3000) = 0x7f9ee0ab7000
mmap(0x7f9ee0ace000, 16384, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1a000) = 0x7f9ee0ace000
mmap(0x7f9ee0ad2000, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1d000) = 0x7f9ee0ad2000
mmap(0x7f9ee0ad3000, 296, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f9ee0ad3000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\320v\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=2224288, ...}, AT_EMPTY_PATH) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
mmap(NULL, 1953104, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9ee0543000
mmap(0x7f9ee0569000, 1400832, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x26000) = 0x7f9ee0569000
mmap(0x7f9ee06bf000, 339968, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x17c000) = 0x7f9ee06bf000
mmap(0x7f9ee0712000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1ce000) = 0x7f9ee0712000
mmap(0x7f9ee0718000, 32080, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f9ee0718000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libnghttp2.so.14", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=173696, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 172112, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9ee0a89000
mmap(0x7f9ee0a8e000, 86016, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x5000) = 0x7f9ee0a8e000
mmap(0x7f9ee0aa3000, 53248, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1a000) = 0x7f9ee0aa3000
mmap(0x7f9ee0ab0000, 16384, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x26000) = 0x7f9ee0ab0000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libidn2.so.0", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=311408, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f9ee0a87000
mmap(NULL, 311304, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9ee0a3a000
mmap(0x7f9ee0a3e000, 20480, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x4000) = 0x7f9ee0a3e000
mmap(0x7f9ee0a43000, 266240, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x9000) = 0x7f9ee0a43000
mmap(0x7f9ee0a84000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x49000) = 0x7f9ee0a84000
mmap(0x7f9ee0a86000, 8, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f9ee0a86000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libssl.so.3", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=677496, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 665584, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9ee04a0000
mmap(0x7f9ee04be000, 372736, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e000) = 0x7f9ee04be000
mmap(0x7f9ee0519000, 114688, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x79000) = 0x7f9ee0519000
mmap(0x7f9ee0535000, 57344, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x94000) = 0x7f9ee0535000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libcrypto.so.3", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=4455088, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 4367384, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9ee0000000
mprotect(0x7f9ee00ad000, 3284992, PROT_NONE) = 0
mmap(0x7f9ee00ad000, 2453504, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0xad000) = 0x7f9ee00ad000
mmap(0x7f9ee0304000, 827392, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x304000) = 0x7f9ee0304000
mmap(0x7f9ee03cf000, 364544, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x3ce000) = 0x7f9ee03cf000
mmap(0x7f9ee0428000, 9240, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f9ee0428000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libgssapi_krb5.so.2", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=359648, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 355096, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9ee0449000
mprotect(0x7f9ee0455000, 294912, PROT_NONE) = 0
mmap(0x7f9ee0455000, 241664, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0xc000) = 0x7f9ee0455000
mmap(0x7f9ee0490000, 49152, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x47000) = 0x7f9ee0490000
mmap(0x7f9ee049d000, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x53000) = 0x7f9ee049d000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libz.so.1", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=103296, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 102408, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9ee042f000
mmap(0x7f9ee0432000, 57344, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x3000) = 0x7f9ee0432000
mmap(0x7f9ee0440000, 28672, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x11000) = 0x7f9ee0440000
mmap(0x7f9ee0447000, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x17000) = 0x7f9ee0447000
mmap(0x7f9ee0448000, 8, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f9ee0448000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libunistring.so.2", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=1800976, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f9ee0a38000
mmap(NULL, 1800392, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9edfe48000
mprotect(0x7f9edfe5a000, 1708032, PROT_NONE) = 0
mmap(0x7f9edfe5a000, 270336, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x12000) = 0x7f9edfe5a000
mmap(0x7f9edfe9c000, 1433600, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x54000) = 0x7f9edfe9c000
mmap(0x7f9edfffb000, 20480, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1b2000) = 0x7f9edfffb000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libkrb5.so.3", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=916064, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 902256, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9edfd6b000
mprotect(0x7f9edfd8e000, 696320, PROT_NONE) = 0
mmap(0x7f9edfd8e000, 438272, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x23000) = 0x7f9edfd8e000
mmap(0x7f9edfdf9000, 253952, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x8e000) = 0x7f9edfdf9000
mmap(0x7f9edfe38000, 65536, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0xcc000) = 0x7f9edfe38000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libk5crypto.so.3", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=99976, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 98416, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9edfd52000
mmap(0x7f9edfd57000, 53248, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x5000) = 0x7f9edfd57000
mmap(0x7f9edfd64000, 16384, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x12000) = 0x7f9edfd64000
mmap(0x7f9edfd68000, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x15000) = 0x7f9edfd68000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libcom_err.so.2", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=24496, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 24640, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9edfd4b000
mmap(0x7f9edfd4d000, 8192, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x2000) = 0x7f9edfd4d000
mmap(0x7f9edfd4f000, 4096, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x4000) = 0x7f9edfd4f000
mmap(0x7f9edfd50000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x4000) = 0x7f9edfd50000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libkrb5support.so.0", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=67312, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 66192, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9edfd3a000
mmap(0x7f9edfd3e000, 32768, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x4000) = 0x7f9edfd3e000
mmap(0x7f9edfd46000, 12288, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0xc000) = 0x7f9edfd46000
mmap(0x7f9edfd49000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0xe000) = 0x7f9edfd49000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libkeyutils.so.1", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=24704, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 24584, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9edfd33000
mmap(0x7f9edfd35000, 8192, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x2000) = 0x7f9edfd35000
mmap(0x7f9edfd37000, 4096, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x4000) = 0x7f9edfd37000
mmap(0x7f9edfd38000, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x4000) = 0x7f9edfd38000
mmap(0x7f9edfd39000, 8, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f9edfd39000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libresolv.so.2", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=67824, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 76360, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9edfd20000
mprotect(0x7f9edfd23000, 49152, PROT_NONE) = 0
mmap(0x7f9edfd23000, 36864, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x3000) = 0x7f9edfd23000
mmap(0x7f9edfd2c000, 8192, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0xc000) = 0x7f9edfd2c000
mmap(0x7f9edfd2f000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0xe000) = 0x7f9edfd2f000
mmap(0x7f9edfd31000, 6728, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f9edfd31000
close(3)                                = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f9ee0a36000
openat(AT_FDCWD, "/lib64/libselinux.so.1", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=176816, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 181896, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9edfcf3000
mprotect(0x7f9edfcf9000, 143360, PROT_NONE) = 0
mmap(0x7f9edfcf9000, 110592, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x6000) = 0x7f9edfcf9000
mmap(0x7f9edfd14000, 28672, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x21000) = 0x7f9edfd14000
mmap(0x7f9edfd1c000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x7f9edfd1c000
mmap(0x7f9edfd1e000, 5768, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f9edfd1e000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libpcre2-8.so.0", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=642072, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 639536, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9edfc56000
mprotect(0x7f9edfc59000, 622592, PROT_NONE) = 0
mmap(0x7f9edfc59000, 442368, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x3000) = 0x7f9edfc59000
mmap(0x7f9edfcc5000, 176128, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x6f000) = 0x7f9edfcc5000
mmap(0x7f9edfcf1000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x9a000) = 0x7f9edfcf1000
close(3)                                = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f9ee0a34000
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f9ee042c000
arch_prctl(ARCH_SET_FS, 0x7f9ee042c840) = 0
set_tid_address(0x7f9ee042cb10)         = 1903122
set_robust_list(0x7f9ee042cb20, 24)     = 0
rseq(0x7f9ee042d160, 0x20, 0, 0x53053053) = 0
mprotect(0x7f9ee0712000, 16384, PROT_READ) = 0
mprotect(0x7f9edfcf1000, 4096, PROT_READ) = 0
mprotect(0x7f9edfd1c000, 4096, PROT_READ) = 0
mprotect(0x7f9edfd2f000, 4096, PROT_READ) = 0
mprotect(0x7f9edfd38000, 4096, PROT_READ) = 0
mprotect(0x7f9ee0447000, 4096, PROT_READ) = 0
mprotect(0x7f9ee03cf000, 352256, PROT_READ) = 0
mprotect(0x7f9edfd49000, 4096, PROT_READ) = 0
mprotect(0x7f9edfd50000, 4096, PROT_READ) = 0
mprotect(0x7f9edfd68000, 8192, PROT_READ) = 0
mprotect(0x7f9edfe38000, 57344, PROT_READ) = 0
mprotect(0x7f9edfffb000, 16384, PROT_READ) = 0
mprotect(0x7f9ee049d000, 8192, PROT_READ) = 0
mprotect(0x7f9ee0535000, 40960, PROT_READ) = 0
mprotect(0x7f9ee0a84000, 8192, PROT_READ) = 0
mprotect(0x7f9ee0ab0000, 12288, PROT_READ) = 0
mprotect(0x7f9ee0ad2000, 4096, PROT_READ) = 0
mprotect(0x7f9ee07fe000, 4096, PROT_READ) = 0
mprotect(0x7f9ee0a23000, 53248, PROT_READ) = 0
mprotect(0x7f9ee0b51000, 8192, PROT_READ) = 0
mprotect(0x407000, 4096, PROT_READ)     = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f9edfc54000
mprotect(0x7f9ee0ba3000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x7f9ee0b56000, 96323)           = 0
statfs("/sys/fs/selinux", {f_type=SELINUX_MAGIC, f_bsize=4096, f_blocks=0, f_bfree=0, f_bavail=0, f_files=0, f_ffree=0, f_fsid={val=[0, 0]}, f_namelen=255, f_frsize=4096, f_flags=ST_VALID|ST_NOSUID|ST_NOEXEC|ST_RELATIME}) = 0
statfs("/sys/fs/selinux", {f_type=SELINUX_MAGIC, f_bsize=4096, f_blocks=0, f_bfree=0, f_bavail=0, f_files=0, f_ffree=0, f_fsid={val=[0, 0]}, f_namelen=255, f_frsize=4096, f_flags=ST_VALID|ST_NOSUID|ST_NOEXEC|ST_RELATIME}) = 0
getrandom("\x78\x7f\x72\xc3\x13\xf6\xd3\x72", 8, GRND_NONBLOCK) = 8
brk(NULL)                               = 0x81c000
brk(0x83d000)                           = 0x83d000
access("/etc/selinux/config", F_OK)     = 0
futex(0x7f9ee0a316bc, FUTEX_WAKE_PRIVATE, 2147483647) = 0
futex(0x7f9ee0427b84, FUTEX_WAKE_PRIVATE, 2147483647) = 0
futex(0x7f9ee0427b80, FUTEX_WAKE_PRIVATE, 2147483647) = 0
futex(0x7f9ee0427b7c, FUTEX_WAKE_PRIVATE, 2147483647) = 0
futex(0x7f9ee0427f00, FUTEX_WAKE_PRIVATE, 2147483647) = 0
futex(0x7f9ee0427b74, FUTEX_WAKE_PRIVATE, 2147483647) = 0
futex(0x7f9ee0427b70, FUTEX_WAKE_PRIVATE, 2147483647) = 0
futex(0x7f9ee0427888, FUTEX_WAKE_PRIVATE, 2147483647) = 0
futex(0x7f9ee0427a60, FUTEX_WAKE_PRIVATE, 2147483647) = 0
futex(0x7f9ee0427790, FUTEX_WAKE_PRIVATE, 2147483647) = 0
brk(0x85e000)                           = 0x85e000
futex(0x7f9ee0427b78, FUTEX_WAKE_PRIVATE, 2147483647) = 0
openat(AT_FDCWD, "/etc/pki/tls/openssl.cnf", O_RDONLY) = 3
futex(0x7f9ee0427510, FUTEX_WAKE_PRIVATE, 2147483647) = 0
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=12171, ...}, AT_EMPTY_PATH) = 0
read(3, "#\n# OpenSSL example configuratio"..., 4096) = 4096
newfstatat(AT_FDCWD, "/etc/crypto-policies/back-ends/opensslcnf.config", {st_mode=S_IFREG|0644, st_size=730, ...}, 0) = 0
openat(AT_FDCWD, "/etc/crypto-policies/back-ends/opensslcnf.config", O_RDONLY) = 4
newfstatat(4, "", {st_mode=S_IFREG|0644, st_size=730, ...}, AT_EMPTY_PATH) = 0
read(4, "CipherString = @SECLEVEL=2:kEECD"..., 4096) = 730
read(4, "", 4096)                       = 0
close(4)                                = 0
read(3, "ch\norganizationName\t= match\norga"..., 4096) = 4096
read(3, "ride a supported extension:\n# ba"..., 4096) = 3979
read(3, "", 4096)                       = 0
close(3)                                = 0
futex(0x7f9ee0427758, FUTEX_WAKE_PRIVATE, 2147483647) = 0
futex(0x7f9ee0427860, FUTEX_WAKE_PRIVATE, 2147483647) = 0
futex(0x7f9ee0427b60, FUTEX_WAKE_PRIVATE, 2147483647) = 0
futex(0x7f9ee0427b5c, FUTEX_WAKE_PRIVATE, 2147483647) = 0
futex(0x7f9ee0427760, FUTEX_WAKE_PRIVATE, 2147483647) = 0
futex(0x7f9ee0427b6c, FUTEX_WAKE_PRIVATE, 2147483647) = 0
futex(0x7f9ee0427724, FUTEX_WAKE_PRIVATE, 2147483647) = 0
futex(0x7f9ee05427c0, FUTEX_WAKE_PRIVATE, 2147483647) = 0
sysinfo({uptime=2291635, loads=[62176, 84224, 78176], totalram=67315396608, freeram=8233512960, sharedram=259239936, bufferram=3250176000, totalswap=8589930496, freeswap=8582328320, procs=1405, totalhigh=0, freehigh=0, mem_unit=1}) = 0
futex(0x7f9ee05427d4, FUTEX_WAKE_PRIVATE, 2147483647) = 0
socket(AF_INET6, SOCK_DGRAM, IPPROTO_IP) = 3
close(3)                                = 0
socketpair(AF_UNIX, SOCK_STREAM, 0, [3, 4]) = 0
fcntl(3, F_GETFL)                       = 0x2 (flags O_RDWR)
fcntl(3, F_SETFL, O_RDWR|O_NONBLOCK)    = 0
fcntl(4, F_GETFL)                       = 0x2 (flags O_RDWR)
fcntl(4, F_SETFL, O_RDWR|O_NONBLOCK)    = 0
rt_sigaction(SIGPIPE, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
poll([{fd=3, events=POLLIN}], 1, 0)     = 0 (Timeout)
rt_sigaction(SIGPIPE, NULL, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, 8) = 0
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
socketpair(AF_UNIX, SOCK_STREAM, 0, [5, 6]) = 0
rt_sigaction(SIGRT_1, {sa_handler=0x7f9ee05cb560, sa_mask=[], sa_flags=SA_RESTORER|SA_ONSTACK|SA_RESTART|SA_SIGINFO, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
rt_sigprocmask(SIG_UNBLOCK, [RTMIN RT_1], NULL, 8) = 0
mmap(NULL, 8392704, PROT_NONE, MAP_PRIVATE|MAP_ANONYMOUS|MAP_STACK, -1, 0) = 0x7f9edf453000
mprotect(0x7f9edf454000, 8388608, PROT_READ|PROT_WRITE) = 0
rt_sigprocmask(SIG_BLOCK, ~[], [], 8)   = 0
clone3({flags=CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_THREAD|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID, child_tid=0x7f9edfc53990, parent_tid=0x7f9edfc53990, exit_signal=0, stack=0x7f9edf453000, stack_size=0x7ffe80, tls=0x7f9edfc536c0} => {parent_tid=[1903125]}, 88) = 1903125
rt_sigprocmask(SIG_SETMASK, [], NULL, 8) = 0
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
poll([{fd=5, events=POLLIN}, {fd=3, events=POLLIN}], 2, 1) = 0 (Timeout)
rt_sigaction(SIGPIPE, NULL, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, 8) = 0
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
poll([{fd=5, events=POLLIN}, {fd=3, events=POLLIN}], 2, 1) = 1 ([{fd=5, revents=POLLIN}])
rt_sigaction(SIGPIPE, NULL, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, 8) = 0
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
close(6)                                = 0
close(5)                                = 0
socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) = 5
setsockopt(5, SOL_TCP, TCP_NODELAY, [1], 4) = 0
fcntl(5, F_GETFL)                       = 0x2 (flags O_RDWR)
fcntl(5, F_SETFL, O_RDWR|O_NONBLOCK)    = 0
connect(5, {sa_family=AF_INET, sin_port=htons(443), sin_addr=inet_addr("52.149.246.39")}, 16) = -1 EINPROGRESS (Operation now in progress)
poll([{fd=5, events=POLLPRI|POLLOUT|POLLWRNORM}], 1, 0) = 0 (Timeout)
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
poll([{fd=5, events=POLLOUT}, {fd=3, events=POLLIN}], 2, 0) = 0 (Timeout)
rt_sigaction(SIGPIPE, NULL, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, 8) = 0
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
poll([{fd=5, events=POLLPRI|POLLOUT|POLLWRNORM}], 1, 0) = 0 (Timeout)
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
poll([{fd=5, events=POLLOUT}, {fd=3, events=POLLIN}], 2, 199) = 1 ([{fd=5, revents=POLLOUT}])
rt_sigaction(SIGPIPE, NULL, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, 8) = 0
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
poll([{fd=5, events=POLLPRI|POLLOUT|POLLWRNORM}], 1, 0) = 1 ([{fd=5, revents=POLLOUT|POLLWRNORM}])
getsockopt(5, SOL_SOCKET, SO_ERROR, [0], [4]) = 0
getpeername(5, {sa_family=AF_INET, sin_port=htons(443), sin_addr=inet_addr("52.149.246.39")}, [128 => 16]) = 0
getsockname(5, {sa_family=AF_INET, sin_port=htons(35876), sin_addr=inet_addr("10.63.1.71")}, [128 => 16]) = 0
futex(0x7f9ee0427f70, FUTEX_WAKE_PRIVATE, 2147483647) = 0
getpid()                                = 1903122
brk(0x87f000)                           = 0x87f000
getrandom("\x8e\x8f\xd3\xb6\x25\xdb\x18\x39\xf4\xed\xb7\x08\x54\xbf\xf8\xe3\xa7\x62\x0d\xcc\xc5\x35\x11\x99\x4e\x01\x5f\x35\x34\x9c\x1e\x1c"..., 48, 0) = 48
futex(0x7f9ee05427d0, FUTEX_WAKE_PRIVATE, 2147483647) = 0
futex(0x7f9ee05427c8, FUTEX_WAKE_PRIVATE, 2147483647) = 0
brk(0x8a0000)                           = 0x8a0000
openat(AT_FDCWD, "/etc/crypto-policies/back-ends/openssl.config", O_RDONLY) = 6
newfstatat(6, "", {st_mode=S_IFREG|0644, st_size=151, ...}, AT_EMPTY_PATH) = 0
read(6, "@SECLEVEL=2:kEECDH:kRSA:kEDH:kPS"..., 4096) = 151
close(6)                                = 0
getpid()                                = 1903122
getpid()                                = 1903122
getpid()                                = 1903122
getpid()                                = 1903122
getpid()                                = 1903122
getpid()                                = 1903122
getpid()                                = 1903122
getpid()                                = 1903122
getpid()                                = 1903122
getpid()                                = 1903122
openat(AT_FDCWD, "/etc/pki/tls/certs/ca-bundle.crt", O_RDONLY) = 6
newfstatat(6, "", {st_mode=S_IFREG|0444, st_size=219276, ...}, AT_EMPTY_PATH) = 0
read(6, "# ACCVRAIZ1\n-----BEGIN CERTIFICA"..., 4096) = 4096
read(6, "b8EZ6WdmF/9ARP67Jpi6Yb+tmLSbkyU+"..., 4096) = 4096
read(6, "DjAMBgNVBAcMBU1pbGFuMSMwIQYDVQQK"..., 4096) = 4096
read(6, "4J2dHy8egBzp90SxdbBk6ZrV9/ZFvgrG"..., 4096) = 4096
brk(0x8c1000)                           = 0x8c1000
read(6, "pY1hp8KD+WGePhbJruKNzANBgkqhkiG9"..., 4096) = 4096
read(6, "A1UdIAQRMA8wDQYLKwYBBAGwLQMEAQEw"..., 4096) = 4096
read(6, "ADcAIABCAGEAcgBjAGUAbABvAG4AYQAg"..., 4096) = 4096
read(6, "-----\nMIIFWTCCA0GgAwIBAgIBAjANBg"..., 4096) = 4096
read(6, "zAxWjBWMQswCQYDVQQGEwJDTjEwMC4GA"..., 4096) = 4096
read(6, "eqy3eApyt4jf/7VGFAkK+qDm\nfQjGGoe"..., 4096) = 4096
read(6, "6XEtHWRqSsjAgMBAAGjQjBAMA4GA1UdD"..., 4096) = 4096
read(6, "q9Emd8VRY+WCv2hikLyhF3HqgiIZd8zv"..., 4096) = 4096
read(6, "QXLYtPU2sQ\nF/xlhMcQSZDe28cmk4gmb"..., 4096) = 4096
brk(0x8e2000)                           = 0x8e2000
read(6, "urDC/zXDrPbDdVCYfeU0BsWO/8tqtlbg"..., 4096) = 4096
read(6, "jAoBgNVBAMMIUQtVFJVU1QgUm9vdCBD\n"..., 4096) = 4096
read(6, "op5w==\n-----END CERTIFICATE-----"..., 4096) = 4096
read(6, "X28MzQC7phW1FG\nfp4tn+6OYwwX7Adw9"..., 4096) = 4096
read(6, "j7TG5BO6jm5qu5jF49OokYTurWGT/u4c"..., 4096) = 4096
read(6, "A5n+KGCR\nHTAduGN8qOY1tfrTYXbm1gd"..., 4096) = 4096
read(6, "5\nIEVudHJ1c3QubmV0IExpbWl0ZWQxMz"..., 4096) = 4096
read(6, "E-----\n\n# Entrust Root Certifica"..., 4096) = 4096
brk(0x903000)                           = 0x903000
read(6, "MDAwWjA7MQsw\nCQYDVQQGEwJFUzERMA8"..., 4096) = 4096
read(6, "FwYDVQQDExBHTE9CQUxUUlVTVCAyMDIw"..., 4096) = 4096
read(6, "e3ah5mm5hRm9iYz+re026nO8/4Piy33B"..., 4096) = 4096
read(6, "kwFwYDVQQKExBHbG9i\nYWxTaWduIG52L"..., 4096) = 4096
read(6, "jvOOJckvB595yEunQtYQEgfn7R\n8k8HW"..., 4096) = 4096
read(6, "2Tc7P\nTMozI+gciKqdi0FuFskg5YmezT"..., 4096) = 4096
read(6, "DRzbLrLFPCU3hKTwSUQZqP\nJzLB5UkZv"..., 4096) = 4096
read(6, "MSMwIQYDVQQKDBpDaHVuZ2h3\nYSBUZWx"..., 4096) = 4096
read(6, "BgNVHRMBAf8EBTADAQH/MA4GA1UdDwEB"..., 4096) = 4096
brk(0x924000)                           = 0x924000
read(6, "w/66VQ3KZ+bVdfIrBQuExUHTRgQ18zZs"..., 4096) = 4096
read(6, "8wXDbO/QJLVQnSKwv4cSsPsjLkkxTOTc"..., 4096) = 4096
read(6, "MVTWljcm9zb2Z0IENvcnBvcmF0aW9uMT"..., 4096) = 4096
read(6, "\nEwJIVTERMA8GA1UEBwwIQnVkYXBlc3Q"..., 4096) = 4096
read(6, "KAoICAQCgvlAQjunybEC0BJyFuTHK3C3"..., 4096) = 4096
read(6, "Vf9WVHhLL5hSEBMHfNrMW\nn4rjyduYNM"..., 4096) = 4096
read(6, "I2MzJaMEgxCzAJBgNVBAYTAkJNMRkwFw"..., 4096) = 4096
read(6, "QH/BAQDAgGGMA0GCSqGSIb3DQEBCwUAA"..., 4096) = 4096
read(6, "QUZJUiBST09UIENBMjAeFw0xNTEwMTkw"..., 4096) = 4096
brk(0x945000)                           = 0x945000
read(6, "DwAwggEKAoIBAQCvNS7YrGxVaQZx5RNo"..., 4096) = 4096
read(6, "+2GaR57GIgUssL8gjMunEst\n+3A7caor"..., 4096) = 4096
read(6, "IEF1dGhvcml0eSAtIEcyMB4XDTA5MDkw"..., 4096) = 4096
read(6, "riBIWhMIxkziWMaa5\nO1M/wySTVltpku"..., 4096) = 4096
read(6, "obalRoot Class 3\n-----BEGIN CERT"..., 4096) = 4096
read(6, "OBvwFItIm\n4TFRfTLcDwIDAQABoyMwIT"..., 4096) = 4096
read(6, "WdfJ9b+euPkrL4JWwWeMA0GCSqGSIb3D"..., 4096) = 4096
read(6, "O1CAmujIS2CNUSSUQIpid\nRtLByZ5OGy"..., 4096) = 4096
read(6, "Qmq131BnW2hqIyE4bJ3XYsgjxroMwuRE"..., 4096) = 4096
brk(0x966000)                           = 0x966000
read(6, "Icb9PuISg\njwBUFfyRbVinljvrS5YnzW"..., 4096) = 4096
read(6, "dEwEB/wQFMAMBAf8wHQYDVR0OBBYEFIH"..., 4096) = 4096
read(6, "lY3VyaXR5LmNvbTEk\nMCIGA1UEChMbWF"..., 4096) = 4096
read(6, "HE5r7iOZULJK2v0ZXk\nltd0ZGtxTgI8q"..., 4096) = 4096
read(6, "wD8ofzkpf9/rdcw0Md3f76BB1UwUCAU9"..., 4096) = 4096
read(6, "UmDnNvtiyjPeyq+GtJK97fKHbH88wDwY"..., 4096) = 2188
read(6, "", 4096)                       = 0
close(6)                                = 0
setsockopt(5, SOL_TCP, TCP_ULP, [7564404], 4) = 0
brk(0x987000)                           = 0x987000
getpid()                                = 1903122
getpid()                                = 1903122
getpid()                                = 1903122
write(5, "\26\3\1\2\0\1\0\1\374\3\3$C\312\233\1\350\240\211Oj\237J\346:\346\207@<\32*S"..., 517) = 517
read(5, 0x9660e3, 5)                    = -1 EAGAIN (Resource temporarily unavailable)
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
poll([{fd=5, events=POLLIN}, {fd=3, events=POLLIN}], 2, 88) = 1 ([{fd=5, revents=POLLIN}])
rt_sigaction(SIGPIPE, NULL, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, 8) = 0
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
poll([{fd=5, events=POLLIN|POLLPRI|POLLRDNORM|POLLRDBAND}], 1, 0) = 1 ([{fd=5, revents=POLLIN|POLLRDNORM}])
read(5, "\26\3\3\0z", 5)                = 5
read(5, "\2\0\0v\3\3\353\37\320\314\fq\301\211\10\205\200\340P\303vY\1772\tKw(\\r\371\312"..., 122) = 122
read(5, "\24\3\3\0\1", 5)               = 5
read(5, "\1", 1)                        = 1
read(5, "\27\3\3\0$", 5)                = 5
read(5, "\300E\244|zN\33\r\274`\220\376\271`\307\322\325L\36\234hpd]\346\32\243\2240\242\350\376"..., 36) = 36
read(5, "\27\3\3\v\256", 5)             = 5
read(5, "qK'\262vo\333\0011\205\3514\334\220Rl\212\32\352\221)\270\224\251\32q\216@\376\343\203\371"..., 2990) = 2990
openat(AT_FDCWD, "/etc/localtime", O_RDONLY|O_CLOEXEC) = 6
newfstatat(6, "", {st_mode=S_IFREG|0644, st_size=3552, ...}, AT_EMPTY_PATH) = 0
newfstatat(6, "", {st_mode=S_IFREG|0644, st_size=3552, ...}, AT_EMPTY_PATH) = 0
read(6, "TZif2\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\6\0\0\0\6\0\0\0\0"..., 4096) = 3552
lseek(6, -2260, SEEK_CUR)               = 1292
read(6, "TZif2\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\6\0\0\0\6\0\0\0\0"..., 4096) = 2260
close(6)                                = 0
read(5, "\27\3\3\1\31", 5)              = 5
read(5, "\"O\2-\304\17!z$\241\235\331\334m\213\267\36W\327&\247\207\331e\363\226\211\361\273\337\226\363"..., 281) = 281
read(5, "\27\3\3\0E", 5)                = 5
read(5, "\314\254,.c\32\304\267g\377\26W\26(~wm\364\272\265\362\3\375\337AI\370W\212\274r`"..., 69) = 69
write(5, "\24\3\3\0\1\1\27\3\3\0E\vx\321\302\354\360A|\t9\235\10\374*\262\33:\261uT\230"..., 80) = 80
write(5, "\27\3\3\0)\247\t\314\271Z\"sn\260\225\243\33\240\221\365\342\v3@\343!\2775\5\272\36\37"..., 46) = 46
write(5, "\27\3\3\0,\312\333\316\345N\tz\264\r\272.\22\277\1\226Ey\255&Y\7\255\362vW\35\261"..., 49) = 49
write(5, "\27\3\3\0\36f{\244\376\230\217N%\264\6e\327\4\344\360\365\36\2\273\3652\222\271\347\243A\352"..., 35) = 35
write(5, "\27\3\3\0@I\240\34\213-\"(\240\245\363'A\253s,\270]i\260\313\35\202\331=(#\327"..., 69) = 69
poll([{fd=5, events=POLLIN|POLLPRI|POLLRDNORM|POLLRDBAND}], 1, 0) = 0 (Timeout)
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
poll([{fd=5, events=POLLIN}, {fd=3, events=POLLIN}], 2, 46) = 1 ([{fd=5, revents=POLLIN}])
rt_sigaction(SIGPIPE, NULL, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, 8) = 0
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
poll([{fd=5, events=POLLIN|POLLPRI|POLLRDNORM|POLLRDBAND}], 1, 0) = 1 ([{fd=5, revents=POLLIN|POLLRDNORM}])
read(5, "\27\3\3\1\32", 5)              = 5
read(5, "\234\352\205\234\324\326[\375\251s\305]YU\329\336\370\313\252\262\306\301\265*8\3.\342\355\10\250"..., 282) = 282
brk(0x9a9000)                           = 0x9a9000
read(5, "\27\3\3\1\32", 5)              = 5
read(5, "\3f\16k\376\177\3447\306\23(^\"\250,\241\33\2512\227\35\20\10\336\215=3\237\23\243C)"..., 282) = 282
read(5, "\27\3\3\09", 5)                = 5
read(5, "\340k\314\277zX\225D\353\366\5j\200\214\232<\327\222\340\370V\365\335[\1G\326\220\361EzF"..., 57) = 57
write(5, "\27\3\3\0\32\216]\17\224\345\334\325A,\341\234#\242\256R\v\322j\212.\250<qL\317\317", 31) = 31
poll([{fd=5, events=POLLIN|POLLPRI|POLLRDNORM|POLLRDBAND}], 1, 0) = 1 ([{fd=5, revents=POLLIN|POLLRDNORM}])
read(5, "\27\3\3\0\32", 5)              = 5
read(5, "\345vy\234\r\273\327N\17\t\236-\36;L\370\264!\177s$\2147\315\366x", 26) = 26
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
poll([{fd=5, events=POLLIN}, {fd=3, events=POLLIN}], 2, 10) = 1 ([{fd=5, revents=POLLIN}])
rt_sigaction(SIGPIPE, NULL, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, 8) = 0
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
poll([{fd=5, events=POLLIN|POLLPRI|POLLRDNORM|POLLRDBAND}], 1, 0) = 1 ([{fd=5, revents=POLLIN|POLLRDNORM}])
read(5, "\27\3\3\0250", 5)              = 5
read(5, "8\2625\2348\274\16Z\264 \365)w\205\231\354\203\307NsX\311\365aC\371\232,Z\2772\222"..., 5424) = 5424
read(5, "\27\3\3\20\32", 5)             = 5
read(5, "\f\231\312P\303_\340_*P\323+\347\345\31\32\225\343\253\271\261.\337\10\37_\27n3\237\317V"..., 4122) = 4122
read(5, "\27\3\3\r\254", 5)             = 5
read(5, "dP\302(h[\363\263#\246\372\230\2108\221GC\264\363\255\307\256\22v\207[D3U\373\366\244"..., 3500) = 248
read(5, 0x97c3e0, 3252)                 = -1 EAGAIN (Resource temporarily unavailable)
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
poll([{fd=5, events=POLLIN}, {fd=3, events=POLLIN}], 2, 8) = 0 (Timeout)
rt_sigaction(SIGPIPE, NULL, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, 8) = 0
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
poll([{fd=5, events=POLLIN|POLLPRI|POLLRDNORM|POLLRDBAND}], 1, 0) = 0 (Timeout)
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
poll([{fd=5, events=POLLIN}, {fd=3, events=POLLIN}], 2, 0) = 0 (Timeout)
rt_sigaction(SIGPIPE, NULL, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, 8) = 0
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
poll([{fd=5, events=POLLIN|POLLPRI|POLLRDNORM|POLLRDBAND}], 1, 0) = 0 (Timeout)
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
poll([{fd=5, events=POLLIN}, {fd=3, events=POLLIN}], 2, 1000) = 1 ([{fd=5, revents=POLLIN}])
rt_sigaction(SIGPIPE, NULL, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, 8) = 0
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
poll([{fd=5, events=POLLIN|POLLPRI|POLLRDNORM|POLLRDBAND}], 1, 0) = 1 ([{fd=5, revents=POLLIN|POLLRDNORM}])
read(5, "\372\231o\302z\235\250\r2\277`\362\314\332!\351\322L+\253\311\350F\244\2453!\204\354\210\237\345"..., 3252) = 3252
read(5, "\27\3\3\0\32", 5)              = 5
read(5, "\33{\323\340(\332n\10^\236~\371\305\374\365U\340\255\325\244W\363O\337\36\355", 26) = 26
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
rt_sigaction(SIGPIPE, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=SA_RESTORER, sa_restorer=0x7f9ee057fb20}, NULL, 8) = 0
newfstatat(1, "", {st_mode=S_IFIFO|0600, st_size=0, ...}, AT_EMPTY_PATH) = 0
write(1, "HaUCk Bank: Securing financial f"..., 146HaUCk Bank: Securing financial freedom since 1982.
Your one-time token/MFA key is 5025. Please provide it to the customer service representative.
) = 146
exit_group(0)                           = ?
+++ exited with 0 +++
```

That's a ton of output. Look, instead, closely at the line

```
connect(5, {sa_family=AF_INET, sin_port=htons(443), sin_addr=inet_addr("52.149.246.39")}, 16) = -1 EINPROGRESS (Operation now in progress)
```

What is the IP address that the HBMA is attempting to access? On what port is it attempting to make a connection?

</details>

## Snooping on Snoopy

We are in agreement that it seems like a Bad Thing (tm) that the HBMA is accessing the Internet. That said, the output from `strace` does not seem to give us even the slightest hint at what information, if any, is being sent over the Internet by this application. Perhaps it's totally inoccuous. We just don't know for sure.

What we would like to be able to do is to look at the data the HBMA sends through the network *once it is in the network*. By taking advantage of that bird's eye view of the information, we are sure that the application cannot trick us. 

Think about what would happen if we attempted to determine what the program was sending over the network by looking just at the application as it ran. Well, if the application were nefarious then it could potentially conceal its activity or even fake us out by leading us to believe that it is sending message $A$ when it is really sending message $B$. But, if we are looking at the data when it is in transit over the network, there is no way we are going to be fooled.

There is an awesome tool named Wireshark that gives us the power to look at the contents of packets transmitted on the network by *any* application on our computer (and even some applications on computers nearby [logically] in the network, under certain circumstances)! How cool is that?

Unlike the tools that we have used so far, Wireshark has a GUI. In order to launch it, 

1. click on the Kali logo in the upper left-hand side of the Desktop,
2. click on grouping named `Sniffing & Spoofing`, and, finally,
3. click on Wireshark.

![](./graphics/wireshark/kali-icon.png)

![](./graphics/wireshark/launch-wireshark.png)

Wireshark is a *very* powerful tool. It gives the malware analyst an incredible number of options. We are going to use a very, *very* small part of its functionality in these exercises.

Our goal is to *sniff* packets in the network that are coming from our computer. Because we are sniffing on the computer that is running the HBMA, we will be able to look at the network traffic it is generating, if there is any! In particular, we will be particularly interested in looking at DNS and HTTP traffic.

> Note: See [above](#description) for information on DNS.

Starting a capture is relatively straightforward when you want to use Wireshark's default settings. Simply double click on the *interface* that you want to *sniff*. An interface is the piece of hardware that connects your computer to the network. Most computers these days have multiple interfaces (e.g., a WiFi interface, a Bluetooth interface, and, perhaps, an Ethernet interface). In order to handle all those cases, we will do a sniffing capture on *any* interface. 

To start a capture, double click on the *any* label.

![](./graphics/wireshark/capture-wireshark.png)

You will start to see a list of all the *packets*, bytes of data grouped together that are meant to be interpreted by a network protocol as related, sniffed from your computer appear on the screen! If you are like me, you will get overwhelmed easily. What we want is a way to narrow down the output to something reasonable.

Again, we want to focus on only the DNS and HTTP traffic. Wireshark lets you filter the traffic that you see using a language that looks a little bit like C. Because we want to display DNS *or* HTTP traffic, it won't surprise you to learn that we are going to be using the `||` symbol. 

![](./graphics/wireshark/display-filter-wireshark.png)

Type

```
dns || http || http2 || http3
```

(Be careful: The names of the *protocols* are case sensitive.)

in the `Display Filter` input box and press Enter. You will see the amount of data displayed shrink considerably.

### Practice

Let's practice before we attempt to decipher the network output of the HBMA. First, stop the current sniffing operation by clicking the red Stop button (right above where you typed the display filter). Restarting a sniffing operation is easier than starting the first sniffing operation -- you can simply click the Shark Fin.

![](./graphics/wireshark/restart-capture-wireshark.png)

Now, in the browser in the guest (*not* the browser on the host computer), type `http://www.example.org` (it is important that you type *exactly* that!). Your screen should fill up with entries that look like 

![](./graphics/wireshark/capture-query-wireshark.png)

How *cool* is that? You are looking at the web browser doing a DNS Query (to turn `example.org` into an IP address that it can access for the web content) followed by an HTTP request (what actually downloads the contents of the web page from the server.)

If you click on the item whose `Info` is something like `Standard Query` you will see some additional information displayed in the bottom-left window. This information is the contents of the actual packet transmitted on the network and Wireshark is formatting the `1`s and `0`s for nice display. Instead of having to piece through the `1`s and `0`s that make up the data in the packet, Wireshark has formatted it nicely. Explore that area and see if you can find where the actual DNS Query is listed. If you need help, you might want to research the concept of a [DNS Query](https://www.cloudns.net/wiki/article/254/).

> Bonus: Try to find the response to the query and determine what IP address corresponds to `example.org`.

An HTTP *get* is an operation that, well, *get*s content from a web server. To be more precise, it is a directive that your brower issues to the client to get the data. The server will respond to that polite request with the data. Click on the item that looks like it will show a packet that contains information about a get operation. It should be fairly easy to see! Then, use your new Wireshark skills to figure out the *version* of the HTTP protocol being used. If you need help, you might want to research the [HTTP header](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers).

### Do

Display the DNS and HTTP packets that are generated by an execution of the HBMA. First, start a capture on the *any* interface. Then, once the capture is running, execute the HBMA. You will need to sniff and execute the HBMA on the same machine (the guest).

<details><summary>Answer</summary>

How frustrating! We only see some DNS queries. That's really odd. (See below). However, we can derive some information from those queries.

Your display should look something like

![](./graphics/wireshark/dns-explore-wireshark.png)

It looks like the malware was attempting to connect to the `duckduckgo.com` website. If we dig deeper, we can find out the IP address of the `duckduckgo.com` website returned from the DNS query. Click on the packet with the Info that contains text something like "Standard query response ..."

![](./graphics/wireshark/dns-query-wireshark.png)

Just like we saw before, that will cause Wireshark to bring up the details of the DNS query response packet. Click on `Answers`.

![](./graphics/wireshark/dns-answer-wireshark.png)

Does the IP address in the response to your query differ from the one shown here?

![](./graphics/wireshark/dns-answer-details-wireshark.png)

</details>

## Static vs. Dynamic Analysis

To this point in our analysis of the HBMA, we have been doing *dynamic* analysis. Dynamic analysis is any analysis conducted on a program while it is executing. As you can imagine, performing dynamic analysis is not always easy or even possible. For example, if we have an executable designed to run on a computer with a processor that we cannot access (e.g., we have an Intel-based computer [x86] and the executable is built for an Arm-based computer [aarch64]), then we cannot run the program. What's more, even if we could run the program it might not be the best idea -- if the program even *might* be  malicious then we would have to be very careful as we execute it.

In these cases we would use *static* analysis, analysis performed on a program without running it. In other words, static analysis is a study of a program only by looking at its contents on disk. There are a number of reasons that this analysis is more difficult than dynamic analysis. However, static analysis is safer and, if done right, more powerful than dynamic analysis.

## Playing With a Ball of Twine

Programs that need to display information to the user or send the same data over the Internet *every* time that it is executed will oftentimes *embed* those data in the program file itself. By looking at these strings we can usually determine something interesting about the program. I mean, if the program contains the string "Password:" our ears will perk up -- just why does this program need a password and what is it going to do with it? Analysing the strings embedded in a file that contains a program is a very straightforward, but useful, form of static analysis.

`strings` is a program that let's us perform this analysis. It takes a single parameter (the path to a file containing a program) and outputs all the strings that are embedded in that program. 

```console
$ strings /path/to/file
```

The `strings` application is not foolproof (e.g., it does not work very well for strings that are encoded with Unicode -- see [below](#hexes-are-for-more-than-curses)). But, the effort/utility ratio is still very high.

### Practice

In the `docs/samples` directory there are two binary programs: `mystery` and `mysteryw`. First, execute them both and compare their outputs.

```console
$ mystery
Emojis make me smile.

$ mysteryw
Emojis make me smile.
```

Does anything look different about their output? Nope, nothing! They are identical. Because those programs output the words `Emojis`, `make`, `me`, `smile` we should expect that the bytes representing the characters in those strings are embedded somewhere in the file that contains the program. Let's use `strings` to verify.

```console
$ strings mystery
...
GLIBCXX_3.4
PTE1
Emojis make me smile.
basic_string: construction from null is not valid
basic_string::_M_create
...
```

Pretty cool!

Now, let's look at the same output for `mysteryw`:

```console
$ strings mysteryw
...
__gmon_start__
_ZNSaIwEC1Ev
_ZNSt7__cxx1112basic_stringIwSt11char_traitsIwESaIwEED1Ev
_ZNSt8ios_base4InitD1Ev
__gxx_personality_v0
_ZNSaIwED1Ev
_ZSt5wcout
_ZStlsIwSt11char_traitsIwEERSt13basic_ostreamIT_T0_ES6_PKc
_ZNSt8ios_base4InitC1Ev
...
```

Interesting. None of the words in the program's output are listed by `strings`. I wonder what gives?

### Do

See if there are any clues that we can decipher from the output of `strings` as to the functionality of the HBMA.

<details><summary>Answer</summary>

There are really not that many meaningful clues that we can uncover. However, if you are especially eagle eyed, it's possible that you picked up on a few things:

```
clang version 15.0.7 (Fedora 15.0.7-2.fc37)
```

seems to indicate that the HBMA was compiled using the [Clang compiler](https://clang.llvm.org/).

```
/home/hawkinsw/code/uc/CS5138/MiniAssignmentHaUCk/src/hauck-mfa.cpp
...
hauck-mfa.cpp
...
```

seems to indicate that the source code for the program was in a file named `hauck-mfa.cpp`.

</details>

## Hexes Are For More Than Curses

Well, the bytes that compose the words `Emojis`, `make`, `me`, `smile` should be somewhere in the file that makes up the `mysteryw` program. I mean, the words somehow make it to the screen, right? `strings` does not seem to show them, but there *must* be a tool that *will* let us find them! 

You're right, there is! It's called `hexdump`.

>Note: The name `hexdump` comes from the term used for a base-16 number system. The numbers that we normally use (e.g., 0, 5, 17) are awesome and come from a base-10 number system (known as the decimal system after the prefix dec- which comes from the Greek for the word ten). Computers, however, have a different definition of awesome and they believe that counting in binary (a base-2 number system) is better. Binary is very difficult for humans to read and write quickly because it is so verbose. Humans and computers can compromise on base 16, or hexadecimal. For more information about the hexadecimal number system, check out [this great article](https://link.springer.com/article/10.1007/s00283-022-10206-w).

Using `hexdump` is only slightly more difficult than using `strings` (and only because there is a *command-line switch*, a thing that we type that modifies the behavior of a command-line tool, that I encourage you to use but is not required). The way that we will use it, `hexdump` takes a single command-line switch (the `-C`) and a single command-line argument (the path to the file whose contents you want to see, represented as individual bytes).

```console
$ hexdump -C /path/to/file
```

Every line in the output from `hexdump` (with the `-C` command-line switch) follows the same format:

```
00003190  00 01 02 03 04 05 06 07  48 45 4C 50 5F 4D 65 21  |........HELP_Me!|
```

The *thing* before the first two spaces (`00003190`) is the address (in bytes and written in base 16) of the leftmost byte shown on the line (`00`). Between the two spaces and the `|` are the values of the 16 bytes (again, written in base 16) starting at the address written to the left of the two spaces. Each number between the spaces represent the value of a byte at a particular address. In the line shown above, the value of the byte with address `00003195` is `05` and the value of the byte with address `00003198` is `48`. Between the two `|`s at the end of the line is the ASCII representation of those bytes (if they are sensical). The values of the last eight bytes in the row of output shown above correspond to the ASCII characters `HELP_Me!`.

> Note: You can research more about the ASCII standard (which is repetitive in the same way that saying "PIN Number" is repetitive) on [Wikipedia](https://en.wikipedia.org/wiki/ASCII). You should compare the way that characters are encoded in ASCII with the way that they are encoded in Unicode (see below!).

---
<details><summary>Converting between hexadecimal and decimal</summary>

Each byte contains 8 bits. A bit is a single one or zero. There are 256 different unique combinations of 8 ones and zeros. That means that it is possible to represent 256 different numbers with 8 bits (Note that does *not* necessarily mean we can *only* represent 0 through 255 -- there are other ways to map the unique combinations to decimal digits as long as we all agree on the method!). 

Each of the "columns" of a number of decimal contains 10 possible values -- 0 through 9 -- and the columns, reading from right-to-left, represent an ever-increasing multiple of 10. Let's "convert" 23:

$ 23 = (2*10*1) + (3*1) $

Or 143:

$ 143 = (1*10*10*1) + (4*10*1) + (3*1) $

Or 1337:

$ 1337 = (1*10*10*10*1) + (3*10*10*1) + (3*10*1) + (7*1) $

Notice how the number of $10$s multiplied together continues to grow as we move from left-to-right?

That same technique applies to hexadecimal numbers except that we multiply by $16$! Therefore there are $16$ different values for each column. Because using double digits would cause confusion (ie., Is $112$ `1 12` or `11  2`?) we will need to use some additional firepower! The values in each column range between `0` and `f`, as in `0`, `1`, ... `9`, `a`, `b`, `c` ... `f`. Let's convert `16` in hexadecimal to decimal:

$ 16 = (1*16*1) + (6*1) = 24 $

Or, how about `118`:

$ 118 = (1*16*16*1) + (1*16*1) + (8*1) = 280 $

Awesome! Let's add some letters and convert `f2`:

$ f2 = (f * 16 *1) + (2 * 1) = (15 * 16 * 1) + (2 * 1) = 242 $

Try to convert `b3` to decimal. For a real challenge, convert $5196$ to hexadecimal and then meet me at Starbucks!


</details>

---

`hexdump` lets you see the actual, unvarnished values of *every* byte in a file! Amazing!

### Practice

We saw from `strings` that `Emojis make me smile` appears in the file that contains the `mystery` program. We can confirm that with `hexdump`:

```console
$ hexdump -C mystery
...
00003000  01 00 02 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00003010  45 6d 6f 6a 69 73 20 6d  61 6b 65 20 6d 65 20 73  |Emojis make me s|
00003020  6d 69 6c 65 2e 0a 00 62  61 73 69 63 5f 73 74 72  |mile...basic_str|
00003030  69 6e 67 3a 20 63 6f 6e  73 74 72 75 63 74 69 6f  |ing: constructio|
00003040  6e 20 66 72 6f 6d 20 6e  75 6c 6c 20 69 73 20 6e  |n from null is n|
00003050  6f 74 20 76 61 6c 69 64  00 62 61 73 69 63 5f 73  |ot valid.basic_s|
00003060  74 72 69 6e 67 3a 3a 5f  4d 5f 63 72 65 61 74 65  |tring::_M_create|
...
```

What is the address of the byte that represents the `l` in `Emojis make me smile.`? That's right, `00003022`.

We know that `mysteryw` has to contain something similar but different than that -- otherwise `strings` would have shown the output we expected. But, just what is that difference? We can use `hexdump` to see the difference:


```console
$ hexdump -C mystery
...
00002000  01 00 02 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00002010  45 00 6d 00 6f 00 6a 00  69 00 73 00 20 00 6d 00  |E.m.o.j.i.s. .m.|
00002020  61 00 6b 00 65 00 20 00  6d 00 65 00 20 00 73 00  |a.k.e. .m.e. .s.|
00002030  6d 00 69 00 6c 00 65 00  2e 00 0a 00 00 00 0a 00  |m.i.l.e.........|
...
```

Fascinating! It looks like there are `00`s between each of the characters in the string that we do not see in the output. 

> If you want to learn more about this mystery, read up on the [Unicode character encoding protocol](https://unicode.org/consortium/consort.html). Unicode is vital to computing worlwide because it allows computers to represent characters in languages other than English ... and because its how Emojis are defined. Yes, there are real computer scientists out there who spend their professional time defining emojis.

### Do

Use `hexdump` to determine the address of the byte representing the `c` in `curl_global_init`.

<details><summary>Answer</summary>

```console
$ hexdump -C hauck-mfa
...
00000c50  5f 65 61 73 79 5f 70 65  72 66 6f 72 6d 00 63 75  |_easy_perform.cu|
00000c60  72 6c 5f 67 6c 6f 62 61  6c 5f 69 6e 69 74 00 5f  |rl_global_init._|
...
```
It looks like the address is `0000c5e`.

</details>

## The only Difference: Bytes in Memory vs. Bytes on Disk
A computer's CPU can only execute instructions that it can read from *memory*. Therefore, an executing program must exist somewhere in memory and memory is different than *storage*. Memory is *volatile* -- its contents are wiped clean when the computer loses access to power (e.g., when it is powered down or when there is a sudden power outage). That does not make it seem like memory is a good place to put things that you will need in the long term! Storage, on the other hand, is a place where a computer can place things that it needs to remember no matter what happens to its electrical supply. In that sense, storage is *nonvolatile*.

But, what? Haven't we been looking at the contents of programs *on disk*? Yes, we have! However, before the computer starts to execute those programs, the operating system loads them in to memory. In other words, the process of launching a program (double-clicking its icon, for instance) is really about reading the bytes from the program's file stored on disk and loading it to the computer's memory. After the program is loaded, the CPU can begin executing its instructions. Loading programs is *not* an easy task -- there are so many details and everything is different (and yet in many ways the same!) on [every](http://newosxbook.com/toc1.html). [single](https://akkadia.org/drepper/dsohowto.pdf). [platform](https://learn.microsoft.com/en-us/sysinternals/resources/windows-internals#table-of-contents-of-the-7th-edition-part-1). 

The contents of a file that contains a program has *almost* everything that will be in memory when that program executes -- it contains the data used as the source for computation and the instructions that direct the computer how to process that data. However, the data and the instructions are not always in the same order in memory (when the program is executing) as they are in the file on disk. The job of the program loader is to reorganize (if necessary) the order and location and protection of program instructions' and data so that the CPU can do its job. 

The reason it is important to understand this difference is because you may be asked to distinguish between the location of a piece of data in a program *as it exists in memory when the program is executing* and the location of a piece of data in a program *as it is stored on disk and not executing*. The distinction is subtle and even seasoned professionals trip over the difference. The sooner you can train your mind to think about the values of the bytes of a program (whether those bytes are instructions or data) as having different locations depending on whether the program is executing in memory or being stored on disk, the better a malware analyst you will be.

## If Everything Else Is False, The Opposite Must Be True

The preceding might seem too theoretical or abstract to put in to action. I assure you that it's not. In our analysis of the HBMA we are interested in determining what data the application is transmitting over the network. We have seen that our tools so far have been unable to uncover the contents of that transmission. Perhaps our tools just aren't sophisticated enough and the data really *is* somewhere in the HBM program file and we are just not looking in the proper spot.

That's reasonable and there's only one to know for sure. First, let's make some assumptions:

1. HBMA is transmitting some data over the network (a safe assumption given the evidence we have already gathered)
2. The data being transmitted *is* somewhere in the contents of the HBMA program file.

Given a combination of (1) and (2), there must be a function somewhere in the program that uses that data -- namely the function doing the transmission! 

Because we don't have the source code of the HBMA application we do not know what the authors named that function in their source code. However, during our analysis we will call it `send`. 

In order to reference the data, `send` would need to accept a *pointer* to the data to send as a parameter. Great, but (again!) we don't have the source code for the HMBA so how are we going to determine the value of that pointer?

Reverse engineering, that's how! Reverse engineering is the most sophisticated form of malware analysis. It involves looking at the instructions of a program *as they are stored in the file containing that program* and attempting to recreate the program's behavior. To do reverse engineering well we have to be able to mentally act like a CPU and read the program's operations and interpret them the way that a CPU would. Crazy!

Before we attempt to use reverse engineering on HBMA, let's look do some reverse engineering on a far simpler program. Along the way we will learn some very important terminology and facts that we will use later.

Look at the source code of the StringSend application in the `string-send` subdirectory (`string-send.cpp`). It is reproduced here for convenience:

```C
#include <stdio.h>

void send(const char *task) {
    int t = 5;
    printf("%s\n", task);
    return;
}

int main() {
    const char todo[] = "Just do it.";
    send(todo);
    return 0;
}
```

Notice that there is a `send` function that takes a pointer to some data. In the StringSend application, the `send` function does nothing more than print the data to the screen. However, it is easy to imagine it doing something else like, oh, I don't know, *sending it on the network.* I think you see where we are going here.

We are going to analyze the `send` function in this simple application to learn tools and tricks and apply those techniques to the (hypothetically named) `send` function in HBMA. Let's get started!

>Note: Much of what follows will be specific to Linux and something called the SystemV ABI. An ABI, an application binary interface, is like an API. You may have heard of an API before because they are popular ways to expose points of communication between interacting programs. An ABI is a way to expose and coordinate the interaction between programs that exist on the same hardware platform. The System V ABI applies to interacting pieces of code designed to run on various *NIX (e.g., Linux) operating systems. You can read more about the System V ABI at [this](https://wiki.osdev.org/System_V_ABI) wiki page.

## Functions, functions, functions.

Functions are useful ways to wrap up functionality into a nice bundle so that those calculations can be used over and over again. Oftentimes, most of the computations that functions bundle up does not depend on any other outside information (e.g., a function that generates a random number). However, sometimes we have a great candidate for wrapping up a bunch of computations in to a single function ... but there's just one problem! There's a small difference in the behavior depending on outside context. These differences are not big enough to motivate us to write a different function, however, so we just add a *parameter* to the function. When we want to reuse the function's, er, functionality we simply *call* the function with particular *arguments*, values that will fill the *parameters*  during that execution of the code in the function.

In `string-send` the `send` function has a parameter named `task` and we invoke the function with `todo` as the argument on the 2nd line of the `main` function. Just *how*, though, is that value conveyed between the caller (`main`) and the callee (`send`)? That's where the ABI plays a role -- it defines the answer to precisely these types of questions!

Every function requires a bundle of information (maybe better called context) in order to operate properly. That bundle of information goes along with the bundle of functionality and the two things together constitute a function at runtime. Just what goes in this bundle? Well, each function needs some space to hold its local variables and the values of its parameters during a given execution.  that means that there cannot be a single copy of the bundle in memory, although all the bundles for a particular function have a similar structure (I mean, the computer cannot be sure that each invocation of a function will have the same value for its parameters). So, every time that a function is executed, a new bundle of information is created just for that invocation. When the invoked function starts executing, the bundle of information contains the values given for the parameter by the arguments and the contents of the local variables' initial values (if there are any). But that's not all. 

(Optional) The bundle also contains information about the bundle of the function that called it (the so-called *saved base pointer* (BP)).

The bundle also contains information about the point in the program to return to when it is done executing (the so-called *return-address pointer* (RA)). During the execution of the function, the contents of the bundle changes as the function performs assignment operations (etc) and, when the function is complete, the bundle is destroyed -- we don't need it any more (right?) and there's no reason to waste memory!

![](./graphics/Stack%20Frame%20Layout%20and%20Registers.png)

The light green, orange, dark green (optional) and gray boxes in the image above constitute the general format of a bundle. The format of a bundle depends greatly on the which compiler is used. In technical terms, the bundle is known as a *stack frame* or an *activation record*.

Again, a new bundle is generated every time that a function is called. All the bundles exist on the program's *stack*. 

Play the role of the CPU for a second and think about your "mind" at the minute you are executing the code that declares and initializes the variable `t` in the execution of `send` triggered by `send(5)` in the `send-string` program. Obviously the `send` function is executing but, crucially, `main` is still executing too -- it's just frozen and waiting for `send` to finish. In other words, you need to remember two bundles -- one for the invocation of `main` that is frozen but incomplete and one for the invocation of `send` that is incomplete and executing. If you were the computer and had to make sure that the active bundles never overlapped, how would you organize them?

Well, if it were me, I would hang one bundle off the bottom of another (metaphorically) and let gravity keep them apart. The string holding them together would be really small (so small that we couldn't see it) so that there was no wasted space between bundles.

What do you know? This technique is *exactly* what your CPU does! The chain of bundles is stored in the computer on the stack. Every time a function is invoked, a new bundle is added to the bottom of the chain. Every time a function completes, its bundle is removed from the chain. The CPU always keeps a little reminder to itself about how to find the bottom of the chain. That reminder is known as the *stack pointer*. 

(Optional) Some compilers generate code that relies on a little reminder about the address of the *center* of the bundle's contents in memory. This reminder is known as the *base pointer*. 

> (Optional) Remember that little point and think about why such a reference might be required! We will revisit its importance later.

What's really cool about this type of design is that the CPU now only needs to remember two things -- the location of stack and (optional) the location of the base pointer!

When a function starts, the function itself is responsible for adding its bundle to the stack. The code generated by the compiler for every function contains a *prologue*, some code the gets executed before any other code in the function that is responsible for adding the function's bundle to the stack. The compiler knows the size of the bundle which means that it can generate code for the prologue that does not need any outside input. 

Remember that you (you *are* still the the CPU, *aren't you?*) always contain reference to the end of the chain. When the prologue generates a new bundle, it better update that reference, right? 

Oh, and one other thing: The prologue needs to cooperate with the CPU and store the location in the program to continue executing after it is done! Cooperation is possible because the CPU places the address of the place in the program where the program should continue executing upon completion at the tail end of the chain right before it starts executing a new function. Therefore, the prologue does three things:

1. it allocates space on the stack for the bundle;
0. it stashes away the place to continue executing upon its completion (that information will go in the Orange Slot in the image above);
0. (related to (1)) it simply grabs the current value of the stack pointer and updates it based on how much space it needs for its bundle (that will go in the `RSP` slot in the gold in the image above). 

> In memory, as the stack grows the adddresses of the bytes of memory containing the contents of the bundle get smaller. In other words, "the stack grows down".

At the other end of the timeline, when a function completes, it executes a set of compiler-generated instructions that will drop the latest bundle from the chain and transfer program control back to the place in the program *just after* where the function was invoked. This code is known as the *epilogue*. Again, because the compiler knows how big the function's bundle will be, the epilogue code can perform its job without any outside information. The epilogue takes the current value of the stack pointer and adjusts it *upwards* according to the size of the bundle. Then, it finds the return address (remember that one of the jobs of the prologue was to stash it away in a safe place?) and transfers control of the program to that location. Therefore, the prologue does three things:

1. deallocates the space on the chain reserved for the bundle;
1. fetches the place in the code to restart the calling function (that the prologue stashed away); and
1. direct the CPU to continue executing there.

What's so amazing about the prologue and the epilogue is that they work together to do all the maintainence required for the stack! The operating system plays no role, the CPU plays only a minor role -- it's entirely self contained! How amazing! It's a self-perpetuating system!

Remember the `send` function:

```C
void send(const char *task) {
    int t = 5;
    printf("%s\n", task);
    return;
}
```

Although we have not yet seen any machine code let alone learned anything about how to read it, let's take a look at the instructions the compiler generates for the CPU to execute when the `send` function is compiled: 

```asm
0000000000401130 <send>:
  401130:	55                   	push   rbp
  401131:	48 89 e5             	mov    rbp,rsp
  401134:	48 83 ec 10          	sub    rsp,0x10
  401138:	48 89 7d f8          	mov    QWORD PTR [rbp-0x8],rdi
  40113c:	c7 45 f4 05 00 00 00 	mov    DWORD PTR [rbp-0xc],0x5
  401143:	48 8b 75 f8          	mov    rsi,QWORD PTR [rbp-0x8]
  401147:	48 bf 10 20 40 00 00 	movabs rdi,0x402010
  40114e:	00 00 00 
  401151:	b0 00                	mov    al,0x0
  401153:	e8 d8 fe ff ff       	call   401030 <printf@plt>
  401158:	48 83 c4 10          	add    rsp,0x10
  40115c:	5d                   	pop    rbp
  40115d:	c3                   	ret    
  40115e:	66 90                	xchg   ax,ax
  ```

  Unlike in programming (where we call the indvidual units of code *statements* or *expressions*), the indvidual elements of logic in machine code are know as *instructions*. Again, we have not yet even started to look at how to read these instructions, but ... the first three instructions:
  ```
401130:	55                   	push   rbp
401131:	48 89 e5             	mov    rbp,rsp
401134:	48 83 ec 10          	sub    rsp,0x10
  ```

are the `send` function's prologue and the last three instructions:
```asm
401158:	48 83 c4 10          	add    rsp,0x10
40115c:	5d                   	pop    rbp
40115d:	c3                   	ret    
```

are the `send` function's epilogue.

## The Dump Truck of Disassembly

Just how was it possible to extract the operations the compiler generated for the `send` function? Reverse engineering depends on the malware analyst's ability to decipher the semantics of the operations (i.e., what they do!) so it better be possible to read them.

Like `host`, `file`, `strings` and `hexdump`, a command-line tool comes to the rescue. `objdump` (short for *obj*ect *dump*) will decode the contents of an *object file* (the technical term for the files that contain programs) into a list of instructions (among other things).

> Note: An object file contains *more* than just a list of the operations that the program executes. It also contains information about the address of the instruction that starts a program, the location of the bytes where all the strings are stored (remember that from above), among other things. 

`objdump` is no more difficult to *use* than `hexdump` (deciphering that output is, well, a little more tricky!):

```console
$ objdump -MIntel -d <filename>
```

The `-d` flag instructs `objdump` to *d*isassemble the instructions in `filename` and output those instructions in the *Intel* format (there are [two ways of formatting CPU instructions](https://imada.sdu.dk/u/kslarsen/dm546/Material/IntelnATT.htm), Intel and AT&T. For programmers, the Intel format is most aligned with the way that we think about the world.)

There is one small problem ... `objdump` generates a lot of output. There are (at least) two ways around this problem:

1. You can store the output in a file and look at it using a file viewer/editor; or
2. You can direct `objdump` to disassemble only certain functions.

The first solution is the easier one:

```console
$ objdump -MIntel -d <filename> > <where to store the output>
```

where the `>` between the `<filename>` and `<where to store the output>` is an actual `>`.

The second solution is really no harder to use:

```console
$ objdump --disassemble=<function name> -MIntel -d <filename>
```

will instruct `objdump` to disassemble only one particular function.

If that function itself is large, you can combine the two solutions:

```console
$ objdump --disassemble=<function name> -MIntel -d <filename> > <where to store the output>
```

Now that we know *how* to use `objdump`, the question becomes: how to interpret its output?

Recall the output from `objdump` from above:
```asm
0000000000401130 <send>:
  401130:	55                   	push   rbp
  401131:	48 89 e5             	mov    rbp,rsp
  401134:	48 83 ec 10          	sub    rsp,0x10
  401138:	48 89 7d f8          	mov    QWORD PTR [rbp-0x8],rdi
  40113c:	c7 45 f4 05 00 00 00 	mov    DWORD PTR [rbp-0xc],0x5
  401143:	48 8b 75 f8          	mov    rsi,QWORD PTR [rbp-0x8]
  401147:	48 bf 10 20 40 00 00 	movabs rdi,0x402010
  40114e:	00 00 00 
  401151:	b0 00                	mov    al,0x0
  401153:	e8 d8 fe ff ff       	call   401030 <printf@plt>
  401158:	48 83 c4 10          	add    rsp,0x10
  40115c:	5d                   	pop    rbp
  40115d:	c3                   	ret    
  40115e:	66 90                	xchg   ax,ax
```

The first line of the output contains two pieces of information about a function in a program:

1. It's address
2. It's name

Recall the discussion about the difference between the addresses of pieces of a program as they exist in memory and in storage. The address presented here is, well, neither, but it is closer to the former than the latter. Because of defensive technologies adopted by operating systems (i.e., [ALSR](https://blog.morphisec.com/aslr-what-it-is-and-what-it-isnt/)), the address of pieces of a program in memory vary from run to run. That said, it is best to consider the addresses presented by `objdump` as if they are the addresses of program elements in memory.

The remaining lines of the output share a similar format. For purposes of discussion, consider this line of `objdump`'s output:

```asm
  401134:	48 83 ec 10          	sub    rsp,0x10
```

The first piece of information (before the `:`) is the *memory* address of the to-be-displayed instruction. The next piece of information is a series of values of bytes (in hexadecimal format) that constitute the instruction. Like a statement in C my contain keywords like `if` or `then` along with variables, an instruction contains special bytes (known as *opcodes*) along with variables (either as addresses in memory or the names of registers) encoded as numbers. These numbers are encoded in bytes and constitute the operation. Finally, the bytes are decoded into a *mnemonic* -- an English-like rendering of the instruction.

> Note: For reference, you can find an authoritative listing of *all* the instructions supported by x86 processors [online](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html). Be warned, it is thousands of pages long!

### Practice

Use `objdump` to disassemble the `main` function of `string-send` and write the list of operations to `/tmp/string-send.main.obj`.

<details><summary>Answer</summary>

```console
$ objdump -MIntel --disassemble=main string-send/build/StringSend > /tmp/string-send.main.obj
```

The contents of `/tmp/string-send.main.obj` should look like:

```asm

string-send/build/StringSend:     file format elf64-x86-64


Disassembly of section .init:

Disassembly of section .plt:

Disassembly of section .text:

0000000000401160 <main>:
  401160: 55                    push   rbp
  401161: 48 89 e5              mov    rbp,rsp
  401164: 48 83 ec 10           sub    rsp,0x10
  401168: c7 45 fc 00 00 00 00  mov    DWORD PTR [rbp-0x4],0x0
  40116f: 48 8b 04 25 14 20 40  mov    rax,QWORD PTR ds:0x402014
  401176: 00
  401177: 48 89 45 f0           mov    QWORD PTR [rbp-0x10],rax
  40117b: 8b 04 25 1c 20 40 00  mov    eax,DWORD PTR ds:0x40201c
  401182: 89 45 f8              mov    DWORD PTR [rbp-0x8],eax
  401185: 48 8d 7d f0           lea    rdi,[rbp-0x10]
  401189: e8 a2 ff ff ff        call   401130 <send>
  40118e: 31 c0                 xor    eax,eax
  401190: 48 83 c4 10           add    rsp,0x10
  401194: 5d                    pop    rbp
  401195: c3                    ret

Disassembly of section .fini:
```

Can you determine where the prologue and epilogue begin and end?

</details>

## One If By Land, Two If By Sea

Prologues and epilogues play a big role in maintaining the chain of bundles, what is technically called the *run-time stack*. That said, they are necessary but not sufficient.

What we said above was that stack frames contain the values of the parameters for a particular execution of function. The prologue and the epilogue don't seem to contain any instructions on how a function's caller transmits the values of the arguments to the called function so that the called function can match those with its parameters. So, how does that happen?

The assignment of argument values to parameters is part of a complex coordination between the calling function and the called function. The steps to this tango are different for each hardware vendor and operating system (e.g., ARM v. Intel and Windows vs Linux). Part of what makes a compiler so special is that they handle all of these details for a programmer who writes their code in a high-level language.

Each hardware/software combination specifies the conventions to follow in an ABI (in particular, a *calling convention*). The operating systems that descend from the original UNIX operating system (e.g., FreeBSD, Linux, and even macOS) all use the System V ABI. Windows uses a different ABI called the fastcall method. 

> Note: Remember that we are focused on the Linux operating system in this tutorial!

Even within the confines of computers running the Linux operating system, there are different calling convention. In particular, there is a different calling conventions depending on whether the CPU is a 32- or 64-bit CPU. 

> Note: Again, remember that we are focused on software running on operating systems on 64-bit hardware.

Under the specification of the calling convention, the caller will place the values for the arguments in a particular place in memory and the called function will retrieve those values from that location. Because we programmers rely so heavily on functions and call them so often, it is a good idea if the transmission of arguments for parameters happens as quickly as possible.

What is the fastest form of memory in a computer? First, note that we are talking about *memory* (remember the difference between memory and storage that we discussed above?). At a baseline, then, the computer's RAM is *a* form of memory that we could use for transmitting arguments to parameters. However, there is something faster!

On each CPU there are a very small number of variables (technically they are called *registers*) and each of them hold the same amount of memory (8 bytes on a 64-bit computer). The CPU can access the values in those registers very, very quickly (a register's value can be read about 3.4 billion times per second on modern CPUs). Each register has a fixed name -- `rdi`, `rsp`, `rip`, etc.

To take advantage of this speed, the arguments that require fewer than 8 bytes for their storage (*most* of them) transmit their values through registers. The first argument goes in the `rdi` register, the second one goes in the `rsi` register, `rdx`, `rcx` ...


As an example of how a calling convention effects the code that the compiler generates, consider the following (very small) C program:

```C
#include <stdio.h>
#include <stdint.h>

int add4(uint64_t one, uint64_t two, uint64_t three, uint64_t four) {
    return one + two + three + four;
}

int main() {
    int sum = add4(5, 10, 15, 20);
    printf("sum: %d\n", sum);
    return 0;
}
```

`add4` is a simple function that accepts four parameters and returns their sum. Because `int`s require less than 32-bites of storage (8 bytes) we suspect that when `add4` is called from `main`, all four of those arguments will be placed in the registers. In fact, we expect that `5` will be in the register `rdi` and `10` in the register `rsi` and `15` in the register `rdx`, and `20` in the register `rdx`. Let's confirm that by looking at the code the compiler generates for the function call of `add4` in `main`:

```asm
  40115c:	b9 14 00 00 00       	mov    ecx,0x14
  401161:	ba 0f 00 00 00       	mov    edx,0xf
  401166:	be 0a 00 00 00       	mov    esi,0xa
  40116b:	bf 05 00 00 00       	mov    edi,0x5
  401170:	e8 b1 ff ff ff       	call   401126 <add4>
```

> Remind yourself of how to read the format of an assembly-code listing generated by `objdump` before continuing.

First, we want to realize that all the numbers are written in hexadecimal. So, we'll convert them to decimal to see if that helps us with our confirmation task:

| hexadecimal | decimal |
| -- | -- |
| 0x14 | 20 |
| 0xf | 15 |
| 0xa | 10 |
| 0x5 | 5 |

That should help us see something pretty cool:

```asm
  40115c:	b9 14 00 00 00       	mov    ecx,0x14
```

is an instruction that moves the literal value `15` into the register `ecx` -- *so* close to what we expected. Instead of moving `15` into `rcx` the instruction is moving it in to `ecx`. 

But, don't worry! There's no difference here, really! `rcx` is a bigger version of the register `ecx`. Whereas `ecx` can only hold `4` bytes, `rcx` can hold 8 and `ecx` is a subset of `rcx`:

![](./graphics/Nesting%20Registers%20x86_64.png)

Assume that each of the gray rectangles can hold 8 bytes of data. There are 8 gray boxes for a total of 64 bytes of storage. You could fit that entire, long number in a single 64-bit register. We'll pretend that the gray boxes represent, say, `rcx`. So, 


```
rcx = 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
```

There are four gray boxes contained in the blue box -- enough to hold 32-bits. So, the 32-bit register associated with the 64-bit `rxc` register, `ecx`, 

```
ecx = 00 01 02 03 04 05 06 07
```

But wait, it gets better. There are two gray boxes contained in the green box -- enough to hold 16-bits. So, the 16-bit register associated with the 64-bit `rxc` register, `cx`, 

```
cx = 00 01 02 03
```

Wait a second, you say: In C I can write a function with *any* number of parameters (well, almost) and you said there are only a fixed (*and small*!) number of registers. What happens when there are more parameters for a function than there are available registers.

