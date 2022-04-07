all: simple.go
	go build -gcflags '-N -l -m' ./simple.go > simple.esc 2>&1
	go build -gcflags '-N -l -S' ./simple.go > simple.asm 2>&1
	objdump -Mintel -D simple > simple.obj
	hexdump -C simple > simple.hex
	readelf -S simple > simple.sections
clean:
	rm -rf simple simple.obj simple.hex simple.asm simple.esc simple.sections
