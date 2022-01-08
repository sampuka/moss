CFLAGS = -ffreestanding -I../../gnu-efi/inc -I~/Programming/gnu-efi/inc/x86_64 -I~/Programming/gnu-efi/inc/protocol -c
CC = x86_64-w64-mingw32-gcc


all:
	mkdir -p build
	$(CC) $(CFLAGS) -o build/hello.o hello.c
	$(CC) $(CFLAGS) -o build/data.o data.c
	$(CC) -nostdlib -Wl,-dll -shared -Wl,--subsystem,10 -e efi_main -o build/BOOTX64.EFI build/hello.o build/data.o
	dd if=/dev/zero of=build/fat.img bs=1k count=1440
	mformat -i build/fat.img -f 1440 ::
	mmd -i build/fat.img ::/EFI
	mmd -i build/fat.img ::/EFI/BOOT
	mcopy -i build/fat.img build/BOOTX64.EFI ::/EFI/BOOT
	mkdir -p iso
	cp build/fat.img iso
	xorriso -as mkisofs -R -f -e fat.img -no-emul-boot -o build/cdimage.iso iso

run: all
	qemu-system-x86_64 -L .. -pflash ../OVMF.fd -cdrom build/cdimage.iso

clean:
	rm -rf build
	rm -rf iso


#all:
#	mkdir -p build
#	cd bootloader && make && cd ..
#	cd kernel && make && cd ..
#	cd libc && make && cd ..
#	cd drivers && make && cd ..
#	ld -m elf_i386 -o build/moss.bin -Ttext 0x1000 kernel/build/kernel.bin libc/build/libc.bin drivers/build/drivers.bin --oformat binary
#	cat bootloader/build/boot_sector.bin build/moss.bin > build/moss.img
#
#run: all
#	qemu-system-x86_64 -vga std -hda build/moss.img
#
#debug: all
#	qemu-system-x86_64 -S -s -hda build/boot_sector.bin
#
#clean:
#	rm -rf build
#	cd bootloader && make clean && cd ..
#	cd kernel && make clean && cd ..
#	cd libc && make clean && cd ..
#	cd drivers && make clean && cd ..
