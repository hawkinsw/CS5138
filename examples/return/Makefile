all: return objdump hexdump

return: return.o
	gcc -g -o return return.o

objdump: return
	objdump -Mintel -d return > return.obj

return.o: return.c return.S
	gcc -g -c return.c -o return.o

return.S: return.c
	gcc -g -S return.c -masm=intel -o return.S

hexdump: objdump
	hd -c return > return.hex

clean:
	rm -rf return *.o *.S *.obj *.hex
