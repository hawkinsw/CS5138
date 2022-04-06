all: iface.go
	go build -gcflags '-N -l -m' ./iface.go > iface.esc 2>&1
	go build -gcflags '-N -l -S' ./iface.go > iface.asm 2>&1
	objdump -Mintel -D iface > iface.obj
	hexdump -C iface > iface.hex
	readelf -S iface > iface.sections
clean:
	rm -rf iface iface.obj iface.hex iface.asm iface.esc iface.sections
