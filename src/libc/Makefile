all:
	mkdir -p build
	gcc -fno-pie -ffreestanding -m32 -std=c11 -c string.c -o build/string.o
	ld -r -m elf_i386 -o build/libc.bin -Ttext 0x1000 build/string.o

clean:
	rm -rf build
