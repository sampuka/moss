add-symbol-file main.o 0x7c00
target remote | qemu-system-x86_64 -S -gdb stdio -hda boot_sector.asm
