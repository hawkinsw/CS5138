# eBPF Examples

## `connect` System Call Monitor (in eBPF)

This program, written in a combination of Python and eBPF, will log
the name, pid and address of every `connect` system call throughout
the system.

## `exec`-ish Monitor (in eBPF)

This program, written in a combination of Python and eBPF, will log
the pid of every program that attempts to load an elf file and the 
name of the file it attempts to load.
the system.

# Installation
Follow the instructions online at [the IO Visor Project -- the organization that manages the development of the BCC tools.](https://github.com/iovisor/bcc/blob/master/INSTALL.md#ubuntu---source)

## Kali-specific installation

Running `configure.kali.sh` will prepare your environment if you are running
Kali Linux.

# Running

* You will need to be root to run!

```
./connect.py
./exec.py
```
