all:
	mkdir -p build
	cd bootloader && make && cd ..
	cd kernel && make && cd ..
	cd libc && make && cd ..
	cd drivers && make && cd ..
	ld -m elf_i386 -o build/moss.bin -Ttext 0x1000 kernel/build/kernel.bin libc/build/libc.bin drivers/build/drivers.bin --oformat binary
	cat bootloader/build/boot_sector.bin build/moss.bin > build/moss.img

run: all
	qemu-system-x86_64 -vga std -hda build/moss.img

debug: all
	qemu-system-x86_64 -S -s -hda build/boot_sector.bin

clean:
	rm -rf build
	cd bootloader && make clean && cd ..
	cd kernel && make clean && cd ..
	cd libc && make clean && cd ..
	cd drivers && make clean && cd ..
