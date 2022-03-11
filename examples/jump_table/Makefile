all: jump objdump hexdump

jump: jump.o
	gcc -o jump jump.o

jump.o: jump.m4
	m4 jump.m4 | gcc -g -c -o jump.o -x c -

objdump: jump
	objdump -Mintel -d jump > jump.obj

hexdump: jump
	hexdump -C jump > jump.hex

clean:
	rm -rf jump *.o *.S *.obj *.hex
