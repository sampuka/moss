all:
	mkdir -p build
	gcc -fno-pie -ffreestanding -m32 -std=c11 -I../libc -c screen.c -o build/screen.o
	ld -r -m elf_i386 -o build/drivers.bin -Ttext 0x1000 build/screen.o

clean:
	rm -rf build
