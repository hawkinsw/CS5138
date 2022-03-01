all: hello.out

hello.o: hello.asm
	nasm -felf64 -o hello.o hello.asm

hello.out: hello.o
	ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 -o hello.out hello.o -lc

clean:
	rm -rf hello.o hello.out
