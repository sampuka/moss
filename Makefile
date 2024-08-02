#CC := gcc
#CXX := g++
#LD := ld
CC := x86_64-w64-mingw32-gcc
CXX := x86_64-w64-mingw32-g++
LD := x86_64-w64-mingw32-ld

OVMF_DIR := .

BUILD_DIR := build
SRC_DIR := src

GNU_EFI_DIR := $(SRC_DIR)/lib/gnu-efi
INCLUDES := -I$(GNU_EFI_DIR)/inc -I$(GNU_EFI_DIR)/inc/x86_64 -I$(GNU_EFI_DIR)/inc/protocol -I$(SRC_DIR) -I$(SRC_DIR)/libc

COMMONFLAGS := -ffreestanding -fpic -fno-stack-protector -fno-stack-check -fshort-wchar -maccumulate-outgoing-args -mno-red-zone -Wall -Wextra $(INCLUDES)
CFLAGS := -std=c11 -O2 $(COMMONFLAGS)
CXXFLAGS := -std=c++17 -O3 $(COMMONFLAGS)
LDFLAGS := -nostdlib -Wl,-dll -shared -Wl,--subsystem,10 -e efi_main
#LIBS := -L/usr/lib -lgnuefi -lefi
#LIBS := -L$(GNU_EFI_DIR)/x86_64/gnuefi -L$(GNU_EFI_DIR)/x86_64/lib -lefi
#LIBS :=

CSOURCES := \
    uefi/data.c \
    uefi/efi_entry.c \
    uefi/uefi_con.c \
    uefi/uefi_gop.c \
    uefi/uefi_utils.c \
    drivers/screen.c

CXXSOURCES := \
    kernel/kernel_main.cpp \
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

$(BUILD_DIR)/BOOTX64.EFI: $(OBJ)
	#$(CC) -shared -Bsymbolic -T$(GNU_EFI_DIR)/gnuefi/elf_x86_64_efi.lds /usr/lib/crt0-efi-x86_64.o -o $(BUILD_DIR)/BOOTX64.EFI $(OBJS) $(LIBS)
	$(CC) $(LDFLAGS) -o $(BUILD_DIR)/BOOTX64.EFI $(OBJ) $(LIBS)

-include $(DEP)

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/%.c
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
	rm moss.iso
