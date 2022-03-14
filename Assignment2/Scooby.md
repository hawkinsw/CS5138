**Assignment Mechanics**

This assignment is worth 100 points and there are 15 possible extra credit points. The exact breakdown of points per question is available in `submission.txt`. 

This assignment is due on March 28th at 11:59pm. Submit your completed `submission.txt` through Canvas by the deadline. Please do *not* include your name anywhere in the `submission.txt` file (makes anonymous grading possible) but be sure to include your *Hacker Motto*.

## Scooby's Magical Mystery Bus

In this assignment we are going to disassemble and analyse a mysterious program that our front-line security team has spotted stealing data from our network. Our vanguard only knows so much about the program -- that it appears to include a function that copies memory from one place to another. They are convinced that the function is malicious. We are going to determine whether the functionality they flagged is actually malicious or not!

Let's get to work!

### Lay The Groundwork

The first step of our analysis is to get a disassembled version of the suspicious executable. To do that we are going to use `objdump`. Recall that there are two different syntaxes for x86-64 assembly code: AT&T and Intel. We have been learning analysis by looking at Intel-formatted assembly and we will continue to work with that format in this investigation. 

Use the following command to generate a file named `scooby_slim.obj` that includes machine code written in Intel format:

```
$ objdump -Mintel -d scooby_slim > scooby_slim.obj
```

**Digression**

> `gdb` will print disassembled instructions in AT&T format by default. Thankfully there is a way to change its format. Once at the `gdb` command line (i.e., *after* you have started `gdb`), you can issue the `set disassembly-flavor intel` command. 

```
(gdb) set disassembly-flavor intel
```

> You can verify that you correctly set the `disassembly-flavor` using a `show` command, `show disassembly-flavor`.

```
(gdb) show disassembly-flavor 
The disassembly flavor is "intel".
```

> Wouldn't it be nice if we didn't have to type this every time? Yes!! To make the change permanent, you can create a file in your home directory (i.e., `~`) named `.gdbinit` and add the `set disassembly-flavor intel` command to it. The commands in the `~/.gdbinit` file get executed every time `gdb` starts. For reference, here is my `~/.gdbinit` file:

```
set disassembly-flavor intel
set history filename ~/.gdb_history
set history save on
```

We cannot go any further in this investigation unless we have a valid disassembly of `scooby_slim`. Confirm that you did the disassembly correctly by comparing the first twenty lines of your `scooby_slim.obj` file with the following:

```
scooby_slim:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <.init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    rsp,0x8
    1008:	48 8b 05 d9 2f 00 00 	mov    rax,QWORD PTR [rip+0x2fd9]        # 3fe8 <calloc@plt+0x2f78>
    100f:	48 85 c0             	test   rax,rax
    1012:	74 02                	je     1016 <__cxa_finalize@plt-0x3a>
    1014:	ff d0                	call   rax
    1016:	48 83 c4 08          	add    rsp,0x8
    101a:	c3                   	ret    

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 92 2f 00 00    	push   QWORD PTR [rip+0x2f92]        # 3fb8 <calloc@plt+0x2f48>
```

### The Mirror at Barney's

We've become experts at disassembling, at least the practical aspects of creating a disassembled binary file (using `objdump`). For the past several weeks we have been working hard at becoming proficient in *analysing* the semantics of a program by looking at its machine code. Our analysis has been aided by the fact that we have had access to the program's source code. But, we have also been aided by the fact that we have had other metadata available to us. 

Unless told otherwise, a compiler/assembler/linker will leave behind some information that makes disassembly easier. These *symbols* help the disassembler label certain addresses with helpful names. For instance, the disassembler can use symbols to turn 

```
    1159: 0f 1f 80 00 00 00 00  nopl   0x0(%rax)
    1160: f3 0f 1e fa           endbr64
    1164: e9 77 ff ff ff        jmpq   10e0 <calloc@plt+0x70>
    1169: f3 0f 1e fa           endbr64  
    116d: 55                    push   %rbp

```

into 

```
    1159: 0f 1f 80 00 00 00 00  nopl   0x0(%rax)

0000000000001160 <frame_dummy>:
    1160: f3 0f 1e fa           endbr64 
    1164: e9 77 ff ff ff        jmpq   10e0 <register_tm_clones>

0000000000001169 <function_name>:
    1169: f3 0f 1e fa           endbr64 
    116d: 55                    push   %rbp
```

Unfortunately, most programs that are distributed do *not* contain those symbols. A program is *stripped* of symbols in order to save space (or to obfuscate its intentions). We can tell whether a binary (e.g., `a.out`) is stripped or not by using the `file` tool: 

```
$ file a.out
a.out: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=07ef2a721513aa4b9dce2d4bedc22d7fc69903f6, for GNU/Linux 3.2.0, stripped
```

Use the `file` command to find an unstripped program somewhere on the file system of your Kali virtual machine. Hint: Check out the `/usr/share/spike/dcedump/ifids` binary. Next, use the `file` command to find a stripped program somewhere on the file system of your Kali virtual machine. Hint: Look at *any* file in `/usr/bin`. For both the stripped and unstripped binary, record the output of `readelf` in `submission.txt` as the answer to Question 1.

### Finding Functions

Well, we're in trouble. `scooby_slim` is stripped. That means we are too close for missiles and we'll have to switch to guns. Not all hope is lost. Recall from class that there is a prologue that functions ("callees") typically use to complete the creation of the activation record that the caller started. In particular, a function typically starts by stashing away `rbp`, moving the current stack pointer (`rsp`) into `rbp` and then allocating space on the stack for local variables (by adjusting `rsp` down).

In the `.text` section of `scooby_slim` find the likely location of the start of functions. Record the address of these function candidates as the response to Question 2 in `submission.txt`.

You should find only one place in the `.text` section that matches this pattern. We will refer to this address as `$MAIN` -- an evocative name, to be sure.

Does that mean that the address you found is the *only* place in the `.text` segment where code exists that begins a function? No! Remember in class we discussed a type of function that does not call other functions. We gave those functions a technical name and discussed *why* they did not have to allocate space on the stack before they perform their work. Record the technical name for functions that do not call other functions and the reason that they do not have to allocate space on the stack as your answer to Question 3 in `submission.txt`.

### Confirm Our Function Hypothesis

We can use external tools to confirm our hypothesis that the instructions at `$MAIN` are the start of a function. From our memory bank let's pull out this fact: The ELF header contains the address of the first instruction to be executed when the program starts. We can use `readelf` to determine the address of this instruction! Use `readelf` to determine the address of `scooby_slim`'s *entry point*. Record your response as the answer to Question 4 in `submission.txt`.

Let's see if we can conceptualize an execution path between the entry point and the address `$MAIN`. The first several instructions at the entry point do not affect the program counter. The program executes sequentially until the `call` instruction at `0x10a8`.

```
    10a8: ff 15 32 2f 00 00     call   QWORD PTR [rip+0x2f32]        # 3fe0 <calloc@plt+0x2f70>
```

This is curious. The call here is unconditional -- the program control will absolutely be transferred to the address *in the eight bytes at `[rip + 0x2f32]`* `objdump` helpfully calculates `$rip + 0x2f32`: `3fe0`. Look through the `objdump` file -- does it contain a snapshot of the byte values at that address? No! 

Despair. Fortunately, we have another set of tools in our toolbelt: `hexdump` and `readelf`. In past Mini Assignments we learned how to a) determine the section of the ELF file containing a given program's address and b) use `hexdump` to determine the initial values of those bytes when the program executes. Use `readelf` and `hexdump` to calculate the *file address* of *program address* `0x3fe0` and the initial value of the 8 bytes at that address. Record your responses as the answer to Question 5.

### Extra Credit: Dynamic Analysis of Program Execution Between 0x10a8 and `$MAIN`

For extra credit, combine your knowledge of the mechanics of dynamic linking and the operation of `gdb` (in particular `starti`, `watch`, `continue`) to trace the execution of `scooby_slim` between `0x10a8` and `$MAIN`. If you would like to undertake this challenge but need some help, please let me know! I am happy to assist! Record your response as the answer to Extra Credit 1 in `submission.txt`.

### What If I Told You ...

At runtime, the contents of the 8 bytes at `0x3fe0` contain a pointer to `__libc_start_main`. As a result, the call at `10a8` invokes this function. Look at the specified behavior of this function online [here](http://refspecs.linux-foundation.org/LSB_4.1.0/LSB-Core-generic/LSB-Core-generic.html#BASELIB---LIBC-START-MAIN-). Wow, this is really cool! We can determine that the function (indirectly) invoked at `0x10a8` will eventually call the function at the *address* in its first parameter. 

Having trouble groking the *type* of the first parameter to `__libc_start_main`? Yes, me too! Fortunately, there's an awesome tool that converts types written in C into "plain" English -- `cdecl`. You will need to install in on Kali:

```
$ sudo apt-get install cdecl
```

Then, run it like this:

```
$ cdecl explain "int (*main) (int, char * *, char * *)"
```

Woah, so much easier to read and just what we expected based on our C knowledge of the signature of `main`. Note: Yes, there *is* a third parameter to `main` and almost everyone (including me) forgets that it is there. The third argument is a pointer to the values of environment variables.

So, what have we learned? We learned that the function called at `0x10a8` will ultimately call the function whose address is in its first parameter. Use your knowledge of the System V Calling Convention to determine the address passed in the first argument to `__libc_start_main`. Record the address as your response to Question 6. It should look eerily similar to `$MAIN`.

Yes, that *was* a bunch of work just to determine that the instructions starting at address `$MAIN` do, indeed, constitute the `main` function of `scooby_slim`. I think it was worth it!

### The Main Course

Take a quick scan of the instructions starting at `$MAIN`. What we can see is that there are no `jmp` instructions between `$MAIN` and the `ret` at `1267`. Without a `jmp`, there's really no way for the function to repeat any instructions. If no instructions are repeated, then there *probably* isn't a loop. 

Remember that our goal is to find and analyse a function that copies memory -- our working hypothesis is that a function that copies memory uses a loop. This assumption is not altogether bad and we will continue to grant the premise until proven wrong.

That means our inscrutable instructions are somewhere else. But, where?

Assume the identity of the CPU for a moment. We will branch out from the `main` function through `call`s at `121c`, `122d`, `1244` and `125c`. `objdump` properly recognizes that the `call`s at `122d` and `125c` are to `calloc` and `printf`, respectively (through the PLT). Because those are functions are provided by the standard library, we will assume that they are not the ones that we want to analyse for malicious behavior.

That leaves us to analyse the code beginning at the addresses `11c1` and `1169`. We will assume (for grammatical purposes) that the code beginning at these addresses constitute functions.

### I'll Help With the Shorter One

Let's start with an analysis of the shorter of the two functions left to analyse. 

```
    11c1: f3 0f 1e fa           endbr64
    11c5: 55                    push   rbp
    11c6: 48 89 e5              mov    rbp,rsp
```
Simply the prologue. We don't need to say anything more!

```
    11c9: 48 89 7d e8           mov    QWORD PTR [rbp-0x18],rdi
```
We know that `rdi` contains the first argument (if it can fit in 8 bytes). This `mov` appears to be storing the value of the first parameter in the 8 bytes
between `rbp - 0x18` and `rbp - 0x10`. We will call the value of these 8 bytes  `param`. 

```
    11cd: 48 c7 45 f8 00 00 00  mov    QWORD PTR [rbp-0x8],0x0
```
This `mov` zero initializes the 8 bytes between `rbp - 0x8` and `rbp`. We will refer to the value of these 8 bytes as `local`. In C, this instruction might translate to

```
int local = 0;
```

We have a curious space of uninitialized bytes on the stack. Record the address (relative to `rbp`) of the 8 allocated but uninitialized bytes on the stack as your answer to Question 7.

```
    11d4: 00
    11d5: 90                    nop
    11d6: 48 8b 45 f8           mov    rax,QWORD PTR [rbp-0x8]
```
We will later determine that the instruction at `11d6` begins the set of instructions that constitute the body of a loop. For now, we will simply note that this instruction loads `local` into register `rax`.

```
    11da: 48 8d 50 01           lea    rdx,[rax+0x1]
```
This instruction is a great example of the way that the `lea` instruction can be used to do normal arithmetic. `lea` is used to add 1 to `rax` and store the result in `rdx`. Yes, this use of the `lea` instruction to essentially perform arithmetic is common.

```
    11de: 48 89 55 f8           mov    QWORD PTR [rbp-0x8],rdx
```
Store `rdx` in `local`. The last two instructions have essentially incremented `local` by one. In C, the preceding two instructions could be written

```
local = local + 1;
```

*Crucially*, however, the value of `rax` *has not changed* from the value that was originally read from memory. So, `rax` contains the value of `local` before it was incremented!
```
    11e2: 48 8b 55 e8           mov    rdx,QWORD PTR [rbp-0x18]
```
Load `param` in to `rdx`. 

```
    11e6: 48 01 d0              add    rax,rdx
```
Add `rdx` to `rax` and store the value in `rax`. Semantically, we know that `rax` now holds `param` + `local` (*before `local` was incremented*)`. In C, we could imagine this looks like

```
int address = param + (local-1);
```

Yes, that variable name was chosen intentionally!

```
    11e9: 0f b6 00              movzx  eax,BYTE PTR [rax]
```

Now, move the byte *at the address* `rax` into `eax` and zero sign extend the 1 byte value so that it fills 4 bytes without changing its meaning. What could possibly be going on here? We can infer that the calculated value of `rax` is some type of a pointer to a byte in memory. It stands to reason that we are loading the byte *at that address* into `eax`. The bottom line is that `rax` (before it is overwritten by this `movz`) is a pointer! We might get the above instruction generated by a compiler that sees (pun intended) C code that looks like:

```
char temp_byte = *address;
```

```
    11ec: 84 c0                 test   al,al
```

The `test` instruction is used will set a flag in the `FLAGS` register based on a bitwise *and* of the contents of its two operands and sets `ZF` of the `FLAGS` register to 1 if the result is 0. `al` is the one-byte version of the `r/eax` register.  In other words,

```
if (the lower 8 bits of r/eax) & (the lower 8 bits of r/eax) == 0 
  ZF = 1; 
else
  ZF = 0;
```
Because the same operand is used on both sides of the bitwise & operator, we can simplify:

```
if (the lower 8 bits of r/eax) == 0
  ZF = 1; 
else
  ZF = 0;
```
```
    11ee: 75 e6                 jne    11d6 <calloc@plt+0x166>
```
`jne` will transfer program control to `11d6` if `ZF = 0`. We can synthesize our accumulation of facts and determine that the combination of the `test` and the `jne` instruction will transfer program control to `11d6` as long as the contents of the byte at `param` + `(local-1)` are not `0`.

In the case where we do *not* transfer control to `11d6` at `11ee`, we continue ...

```
    11f0: 48 8b 45 f8           mov    rax,QWORD PTR [rbp-0x8]
```
Put `local` into `rax`.

```
    11f4: 5d                    pop    rbp
    11f5: c3                    ret
```
From our knowledge of the System V ABI Calling Conventions we know that `rax` holds the return value of a function (if it will fit). `rax`'s value is `local - 1` when the function ends. We can infer, then, that this function returns the value of `local - 1`.

We have lots of facts, but not much knowledge. Let's try to mentally *lift* the machine code into C:

```
int unknown_function(char *param) {
  int local = 0;
  char temp_byte = '\0';
  do {
    local = local + 1;
    int address = (uint64_t)param + (local-1);
    temp_byte = *address;
  } while (temp_byte != 0);
}
return local - 1;
```

The `local - 1` bit is really annoying. Let's rewrite it:

```
int unknown_function(char *param) {
  int local = 0;
  int address = (uint64_t)param + local;
  char temp_byte = *address;
  while (temp_byte != 0) {
    local = local + 1;
    address = (uint64_t)param + local;
    temp_byte = *address;
  }
}
return local;
```

We will do some hocus pocus and deploy our mental C compiler to rewrite that code as

```
int unknown_function(char *param) {
  int local = 0;
  char temp_byte = param[local];
  while (temp_byte != 0) {
    local = local + 1;
    temp_byte = param[local]
  }
}
return local;
```

Let's rename `local` to something more meaningful:

```
int unknown_function(char *param) {
  int index = 0;
  char temp_byte = param[index];
  while (temp_byte != 0) {
    index = index + 1;
    temp_byte = param[index]
  }
}
return index;
```

And, a final rewrite to remove that pesky, useless temporary variable `temp_byte`:

```
int unknown_function(char *param) {
  int index = 0;
  while (param[index] != 0) {
    index = index + 1;
  }
}
return index;
```

I lied. Let's make one final change. From the ASCII table we know that 0 is the same as '\0':

```
int unknown_function(char *param) {
  int index = 0;
  while (param[index] != '\0') {
    index = index + 1;
  }
}
return index;
```

Oh, *now* that looks like some C code that we would really write. In fact, it is likely you *have* written code like this before. Interpret the loop above to determine what it calculates. Hint: [Think about how strings are represented in C](https://www.gnu.org/software/libc/manual/html_node/Representation-of-Strings.html). Record you response as the answer to Question 8 in `submission.txt`. Give this function a meaningful name. Record your response as the answer to Question 9 in `submission.txt`. Congratulations, you just reverse engineered your first function!

### The Training Wheels Are Off

Well, that was a *ton* of work but we did learn something: The function we just disassembled is not the droid we are looking for. That leads us to assume that the function starting at `1169` is the real culprit here.

I'll help you get started with an analysis of this function, but then you are on your own!

```
    1169: f3 0f 1e fa           endbr64
    116d: 55                    push   rbp
    116e: 48 89 e5              mov    rbp,rsp
```
We've seen this movie before -- just do the function prologue work.

```
    1171: 48 89 7d e8           mov    QWORD PTR [rbp-0x18],rdi
    1175: 48 89 75 e0           mov    QWORD PTR [rbp-0x20],rsi
```

Store the first two arguments on the stack. The 8 bytes between `rbp - 0x18` and `rbp - 0x10` contain `rdi`, the first parameter. We will refer to this parameter as `d`. The 8 bytes between `rbp - 0x20` and `rbp - 0x18` contain `rsi`. We will refer to this parameter as `s`.

```
    1179: 48 c7 45 f0 00 00 00  mov    QWORD PTR [rbp-0x10],0x0
    1180: 00
    1181: 48 c7 45 f8 00 00 00  mov    QWORD PTR [rbp-0x8],0x0
    1188: 00
    1189: 90                    nop
```
Create two local variables and initialize them to 0.  We will refer to the value of the 8 bytes between `rbp - 0x10` and `rbp - 0x8` as `c1`. We will refer to the value of the 8 bytes between `rbp - 0x8` and `rbp - 0x0` as `c2`.

```
    118a: 48 8b 45 f8           mov    rax,QWORD PTR [rbp-0x8]
```
Load `c2` into `rax`.

```
    118e: 48 8d 50 01           lea    rdx,[rax+0x1]
    1192: 48 89 55 f8           mov    QWORD PTR [rbp-0x8],rdx
```
Store `c2 + 1` in `c2`. Crucially, though, we *do not* change the value of `rax` which was the initial, unincremented value of `c2`.

```
    1196: 48 8b 55 e0           mov    rdx,QWORD PTR [rbp-0x20]
```
Load `s` into `rdx`.
```
    119a: 48 8d 0c 10           lea    rcx,[rax+rdx*1]
```
Add `rdx` (a.k.a, `s`) to `rax` (a.k.a `c2` *before it was incremented*) and store the result in `rcx`.

```
    119e: 48 8b 45 f0           mov    rax,QWORD PTR [rbp-0x10]
```
Load `c1` into `rax`.

```
    11a2: 48 8d 50 01           lea    rdx,[rax+0x1]
    11a6: 48 89 55 f0           mov    QWORD PTR [rbp-0x10],rdx
```
Add 1 to `c1` and store it in `c1`. Crucially, *do not* change the value of `rdx` which was the initial, unincremented value of `c1`.

```
    11aa: 48 8b 55 e8           mov    rdx,QWORD PTR [rbp-0x18]
```
Load `d` into `rdx`.

```
    11ae: 48 01 d0              add    rax,rdx
```
Add `rdx` (a.k.a `d`) to `rax` (a.k.a `c1` *before it was incremented*).

```
    11b1: 0f b6 11              movzx  edx,BYTE PTR [rcx]
```
Load the byte at the address in `rcx` (after zero extension) into `edx`. What was `rcx`? `s` +  the value of `c2` *before it was incremented*.

```
    11b4: 88 10                 mov    BYTE PTR [rax],dl
```
Store the loaded value back into the address at `rax`. What was `rax`?  `d` + the value of `c1` *before it was incremented*. `dl` is the 8-bit version of the `r/edx` register.

```
    11b6: 0f b6 00              movzx  eax,BYTE PTR [rax]
```
Now, load the value *we just wrote into memory* back into the `eax` register.

```
    11b9: 84 c0                 test   al,al
```
Determine whether `al` (the 8-bit version of the `r/eax` register) contains 0.

```
    11bb: 75 cd                 jne    118a <calloc@plt+0x11a>
```
If it does not, jump back to `118a` and do it again! Otherwise, fall through and finish the function with the next two instructions.

```
    11bf: 5d                    pop    rbp
    11c0: c3                    ret
```
Note that we do *not intentionally* set `rax` before finishing the function. Curious. There are two possible reasons for this omission:

1. The value of `rax` at the point of the return is the function's return value.
2. There is no return value for this function.

Let's assume the latter but we cannot discount the former.

Okay, now it's your turn! As we did for the previous function we disassembled, craft *lifted* C code for the function you just disassembled. Record your response as the answer to Question 10 in `submission.txt`.

With a set of C code to work from, interpret the semantics of the function you just disassembled. Record your response as the answer to Question 11 in `submission.txt`. In the course of your analysis, answer the question posed to you by your analysts: Is this function the one that concerned them and is it really malicious? Finally, name the function and record that as your answer to Question 12 in `submission.txt`.

Wow, you did it! 

### Great Job

As a second, final opportunity for extra credit on this assignment, combine your knowledge of

1. The semantics of the function that you just disassembled (in particular, its parameters)
2. `readelf` for translating between the addresses of program memory and the addresses of the initial value of those bytes in the ELF file
3. `hexdump` for reading the value of bytes in an ELF file

and find the message hidden in the program. Record your response as the answer to Extra Credit 2 in `submission.txt`.