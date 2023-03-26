all: registers.out registers.obj xmm2.out xmm2.obj

registers.o: registers.asm
	nasm -felf64 -o registers.o registers.asm

registers.out: registers.o
	gcc -o registers.out registers.o

registers.obj: registers.out
	objdump -d registers.out > registers.obj

xmm2.o: xmm2.asm
	nasm -felf64 -o xmm2.o xmm2.asm

xmm2.out: xmm2.o
	gcc -o xmm2.out xmm2.o

xmm2.obj: xmm2.out
	objdump -d xmm2.out > xmm2.obj

clean:
	rm -rf registers.o registers.out registers.obj
	rm -rf xmm2.o xmm2.out xmm2.obj
