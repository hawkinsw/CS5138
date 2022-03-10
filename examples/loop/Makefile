all: loop objdump

loop: loop.o
	gcc -g -o loop loop.o

objdump: loop
	objdump -Mintel -d loop > loop.obj

loop.o: loop.c loop.S
	gcc -g -c loop.c -o loop.o

loop.S: loop.c
	gcc -g -S loop.c -masm=intel -o loop.S

clean:
	rm -rf loop *.o *.S *.obj
