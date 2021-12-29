all:
	mkdir -p build
	nasm boot_sector.asm -f bin -o build/boot_sector.bin

run: all
	qemu-system-x86_64 -vga std -hda build/boot_sector.bin

debug: all
	qemu-system-x86_64 -S -s -hda build/boot_sector.bin

clean:
	rm -rf build
