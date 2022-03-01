all: hello.out

hello.o: hello.asm
	nasm -felf64 -o hello.o hello.asm

hello.out: hello.o
	ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 -o hello.out hello.o -lc

hello.obj: hello.out
	objdump -d hello.out > hello.obj

clean:
	rm -rf hello.o hello.out hello.obj
