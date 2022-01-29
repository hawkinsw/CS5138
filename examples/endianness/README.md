## Explore Endianness

`gdb` makes it easy to peek at the actual contents of memory at runtime. Looking at the content of memory
where we have stored a number of our choosing makes it vividly obvious the effect that endianness has on
the layout of numbers in memory.

### Compile

`$ make`

### Observe

Here is a set of instructions you can follow to observe the layout of multi-byte numbers in memory
when run on a Little-Endian machine.

```
┌──(kali㉿kali)-[~/CS5138/examples/endianness]
└─$ gdb endian                                                                                                                          
GNU gdb (Debian 10.1-2) 10.1.90.20210103-git
Copyright (C) 2021 Free Software Foundation, Inc.                                                                                       
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from endian...
(gdb) break main
Breakpoint 1 at 0x112d: file endian.c, line 2.
(gdb) run
Starting program: /home/kali/CS5138/examples/endianness/endian 

Breakpoint 1, main () at endian.c:2
2               unsigned long endian = 0x12345678;
(gdb) step
3               return endian;
(gdb) x/8bx &endian
0x7fffffffdeb8: 0x78    0x56    0x34    0x12    0x00    0x00    0x00    0x00
(gdb) 
```

If we were debugging on a Big-Endian machine, we would have expected to see
the _big end_ of the constant earlier in memory. However, this is a Little-Endian
machine so we see the _little end_ of the constant earlier in memory.

Fascinating.
