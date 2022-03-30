all: final objdump hexdump

final: final.o
	g++ -g -o final final.o

objdump: final
	objdump -Mintel -d final > final.obj

final.o: final.cpp final.S
	g++ -g -c final.cpp -o final.o

final.S: final.cpp
	g++ -g -S final.cpp -masm=intel -o final.S

hexdump: objdump
	hexdump -C final > final.hex

clean:
	rm -rf final *.o *.S *.obj *.hex
