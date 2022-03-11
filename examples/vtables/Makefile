all: table objdump hexdump

table: table.o
	g++ -g -o table table.o

objdump: table
	objdump -Mintel -d table > table.obj

table.o: table.cpp table.S
	g++ -g -c table.cpp -o table.o

table.S: table.cpp
	g++ -g -S table.cpp -masm=intel -o table.S

hexdump: objdump
	hexdump -C table > table.hex

clean:
	rm -rf table *.o *.S *.obj *.hex
