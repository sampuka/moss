all:
	mkdir -p build
	nasm kernel_entry.asm -f elf -o build/kernel_entry.o
	gcc -fno-pie -ffreestanding -m32 -std=c11 -c kernel.c -o build/kernel.o
	gcc -fno-pie -ffreestanding -m32 -std=c11 -c screen/screen.c -o build/screen.o
	ld -m elf_i386 -o build/kernel.bin -Ttext 0x1000 build/kernel_entry.o build/kernel.o build/screen.o --oformat binary

clean:
	rm -rf build
