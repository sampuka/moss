all:
	mkdir -p build
	cd bootloader && make && cd ..
	cd kernel && make && cd ..
	cat bootloader/build/boot_sector.bin kernel/build/kernel.bin > build/moss.img

run: all
	qemu-system-x86_64 -vga std -hda build/moss.img

debug: all
	qemu-system-x86_64 -S -s -hda build/boot_sector.bin

clean:
	rm -rf build
