## `connect` System Call Monitor (in eBPF)

This program, written in a combination of Python and eBPF, will log
the name, pid and address of every `connect` system call throughout
the system.

### Install `bcc`

Follow the instructions online at [the IO Visor Project -- the organization that manages the development of the BCC tools.](https://github.com/iovisor/bcc/blob/master/INSTALL.md#ubuntu---source)

### Running

* You will need to be root to run!

```
./connect.py
```
