all: xmm2.out xmm2.obj

xmm2.o: xmm2.asm
	nasm -felf64 -o xmm2.o xmm2.asm

xmm2.out: xmm2.o
	gcc -o xmm2.out xmm2.o

xmm2.obj: xmm2.out
	objdump -d xmm2.out > xmm2.obj

clean:
	rm -rf xmm2.o xmm2.out xmm2.obj
