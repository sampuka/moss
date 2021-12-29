all:
	mkdir -p build
	nasm boot_sector.asm -f bin -o build/boot_sector.bin

run: all
	qemu-system-x86_64 -hda build/boot_sector.bin

clean:
	rm -rf build
