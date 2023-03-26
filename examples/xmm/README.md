## Wide Load

This simple program demonstrates the value of the bytes in memory that
are subsequently `movsd`'d into the `xmm2` register. It also prints the value
of `xmm2` (as a floating-point value) after the move is complete.

### Compiling

```
make
```

### Running

```
$ ./xmm2.out
```

### What Code?

Take a look at `xmm2.asm` if you are interested in learning more. The code
is fairly straightforward!
