#CC := gcc
#CXX := g++
#LD := ld
CC := x86_64-w64-mingw32-gcc
CXX := x86_64-w64-mingw32-g++
LD := x86_64-w64-mingw32-ld

OVMF_DIR := .

BUILD_DIR := build
SRC_DIR := src
PDCLIB_DIR := $(SRC_DIR)/lib/pdclib

# Oder matters here. Files in /usr/include/ can easily take precedence over others
INCLUDES := -I$(SRC_DIR) -I$(SRC_DIR)/lib/pdclib/include -I$(BUILD_DIR)/pdclib/configured_include -I/usr/include/efi

COMMONFLAGS := -ffreestanding -fpic -fno-stack-protector -fno-stack-check -fshort-wchar -maccumulate-outgoing-args -mno-red-zone -D_PDCLIB_BUILD
CFLAGS := $(COMMONFLAGS) $(INCLUDES) -std=c11 -O2 -Wall -Wextra
CXXFLAGS := $(COMMONFLAGS) $(INCLUDES) -std=c++17 -O3 -Wall -Wextra -fno-exceptions -fno-rtti
LDFLAGS := -mno-red-zone -Wl,-dll -shared -Wl,--subsystem,10 -e efi_main -nostdlib
#LIBS := -L/usr/lib -lgnuefi -lefi
#LIBS := -L$(GNU_EFI_DIR)/x86_64/gnuefi -L$(GNU_EFI_DIR)/x86_64/lib -lefi
LIBS := #-lgcc

PDCLIBSOURCES := \
	lib/pdclib/functions/ctype/isspace.c \
	lib/pdclib/functions/ctype/tolower.c \
	lib/pdclib/functions/stdio/snprintf.c \
	lib/pdclib/functions/stdio/vsnprintf.c \
	lib/pdclib/functions/stdio/putc.c \
	lib/pdclib/functions/stdio/puts.c \
	lib/pdclib/functions/stdio/fputc.c \
	lib/pdclib/functions/stdlib/strtol.c \
	lib/pdclib/functions/stdlib/abs.c \
	lib/pdclib/functions/stdlib/div.c \
	lib/pdclib/functions/string/memchr.c \
	lib/pdclib/functions/string/strlen.c \
	lib/pdclib/functions/string/memcpy.c \
	lib/pdclib/functions/string/memmove.c \
	lib/pdclib/functions/inttypes/imaxdiv.c \
    lib/pdclib/functions/_PDCLIB/_PDCLIB_strtox_prelim.c \
    lib/pdclib/functions/_PDCLIB/_PDCLIB_strtox_main.c \
    lib/pdclib/functions/_PDCLIB/_PDCLIB_print.c \
    lib/pdclib/functions/_PDCLIB/_PDCLIB_prepwrite.c \
    lib/pdclib/functions/_PDCLIB/_PDCLIB_digits.c \
    lib/pdclib/functions/_PDCLIB/_PDCLIB_print_integer.c \
    lib/pdclib/functions/_PDCLIB/_PDCLIB_print_string.c \
    lib/pdclib/functions/_PDCLIB/_PDCLIB_print_fp.c \
    lib/pdclib/functions/_PDCLIB/errno.c \
    lib/pdclib-config/functions/_PDCLIB/_PDCLIB_stdinit.c \
    lib/pdclib-config/functions/_PDCLIB/_PDCLIB_flushbuffer.c \

CSOURCES := \
    uefi/efi_entry.c \
    uefi/uefi_con.c \
    uefi/uefi_gop.c \
    uefi/uefi_utils.c \
    drivers/screen.c

CSOURCES := $(CSOURCES) $(PDCLIBSOURCES)

CXXSOURCES := \
    kernel/kernel_main.cpp \
    application/display_settings.cpp \
    application/graphics_test.cpp

OBJ = $(CSOURCES:%.c=$(BUILD_DIR)/%.c.o) $(CXXSOURCES:%.cpp=$(BUILD_DIR)/%.cpp.o)
DEP = $(OBJ:%.o=%.d)

.PHONY: all run clean

all: moss.iso

moss.iso: $(BUILD_DIR)/BOOTX64.EFI
	dd if=/dev/zero of=$(BUILD_DIR)/fat.img bs=1k count=1440
	mformat -i $(BUILD_DIR)/fat.img -f 1440 ::
	mmd -i $(BUILD_DIR)/fat.img ::/EFI
	mmd -i $(BUILD_DIR)/fat.img ::/EFI/BOOT
	mcopy -i $(BUILD_DIR)/fat.img $(BUILD_DIR)/BOOTX64.EFI ::/EFI/BOOT
	mkdir -p iso
	cp $(BUILD_DIR)/fat.img iso
	xorriso -as mkisofs -R -f -e fat.img -no-emul-boot -o moss.iso iso

$(BUILD_DIR)/pdclib/configured_include/include/_PDCLIB_config.h:
	mkdir -p build/pdclib
	cmake -Ssrc/lib/pdclib -B build/pdclib -DUSE_THREADS=OFF

$(BUILD_DIR)/BOOTX64.EFI: $(OBJ)
	#$(CC) -shared -Bsymbolic -T$(GNU_EFI_DIR)/gnuefi/elf_x86_64_efi.lds /usr/lib/crt0-efi-x86_64.o -o $(BUILD_DIR)/BOOTX64.EFI $(OBJS) $(LIBS)
	$(CC) $(LDFLAGS) $(COMMONFLAGS) -o $(BUILD_DIR)/BOOTX64.EFI $(OBJ) $(LIBS)

-include $(DEP)

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/%.c $(BUILD_DIR)/pdclib/configured_include/include/_PDCLIB_config.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

$(BUILD_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

run: all
	qemu-system-x86_64 -L .. -pflash $(OVMF_DIR)/OVMF.fd -cdrom moss.iso

clean:
	rm -rf $(BUILD_DIR)
	rm -rf iso
	rm -f moss.iso
