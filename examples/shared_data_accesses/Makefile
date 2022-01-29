shared.so: shared.c
	gcc -shared -O0 -o libshared.so shared.c -fPIC
sharer: shared.so sharer.c
	gcc -O0 -o sharer sharer.c -L./ -lshared
run: shared.so sharer
	LD_LIBRARY_PATH=./ ./sharer
debug: shared.so sharer
	LD_LIBRARY_PATH=./ gdb ./sharer
clean:
	rm -rf *.so sharer
