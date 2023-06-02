# Flare

## Using External Libraries
Software developers don't write their code in a vacuum -- they rely on software from others! Malware writers are no different than other software engineers. Malicious hackers want to write code as easily and quickly as possible and that often requires a reliance on other people's work.

### Description

### Practice
`host` is a little command that will perform *DNS resolution* on a hostname. *DNS resolution* is the process of using the domain name system (DNS) to convert a hostname (e.g., `google.com`) into an IP address (e.g., `4.3.2.10` or `2607:f8b0:4009:803::200e`).

Let's see what libraries `host` needs from the host operating system in order to perform its work:

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

## System Calls

### Description

### Practice