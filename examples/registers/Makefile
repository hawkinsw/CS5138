all: registers.out registers.obj

registers.o: registers.asm
	nasm -felf64 -o registers.o registers.asm

registers.out: registers.o
	gcc -o registers.out registers.o

registers.obj: registers.out
	objdump -d registers.out > registers.obj

clean:
	rm -rf registers.o registers.out registers.obj
