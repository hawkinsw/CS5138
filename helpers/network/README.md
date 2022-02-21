### (Un)Configure As ...

These are a few helper scripts to configure a Kali machine to act as a MITM proxy
and router.

### Upgrade `mitmproxy`
In order for SSL key logging to work properly, you *must* install `mitmproxy` version 7.0.4. You can download that from [their website](https://snapshots.mitmproxy.org/7.0.4/mitmproxy-7.0.4-linux.tar.gz).

The easiest way to install, is to unzip the tar file and then copy the binaries to `/usr/bin/`.

```
$ mitmproxy --version
```

should report a version of `7.0.4`:

```
Mitmproxy: 7.0.4 binary
Python:    3.9.7
OpenSSL:   OpenSSL 1.1.1l  24 Aug 2021
Platform:  Linux-5.14.0-kali4-amd64-x86_64-with-glibc2.33
```

#### Tips

Check the source of each of the scripts and make sure that all the variables are 
set properly. 

Execute the scripts as the `root` user -- `sudo` is fine!
