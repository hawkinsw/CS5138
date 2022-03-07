all: sum objdump

sum: main.o sum.o
	gcc -g -o sum main.o sum.o

objdump: sum
	objdump -Mintel -d sum > sum.obj

main.o: main.c main.S
	gcc -g -c main.c -o main.o

sum.o: sum.c sum.S
	clang -g -c sum.c -o sum.o

main.S: main.c
	gcc -g -S main.c -masm=intel -o main.S

sum.S: sum.c
	clang -g -S sum.c -o sum.S

clean:
	rm -rf sum.o main.o main.S sum.S sum sum.obj
