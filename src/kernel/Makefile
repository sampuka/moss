all:
	mkdir -p build
	gcc -ffreestanding -c kernel.c -o build/kernel.o
	ld -o build/kernel.bin -Ttext 0x1000 build/kernel.o --oformat binary

clean:
	rm -rf build
