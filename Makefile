CC := x86_64-w64-mingw32-gcc
CXX := $(CC)

OVMF_DIR := .

GNU_EFI_DIR := ../gnu-efi
INCLUDES := -I$(GNU_EFI_DIR)/inc -I$(GNU_EFI_DIR)/inc/x86_64 -I$(GNU_EFI_DIR)/inc/protocol

CFLAGS := -std=c11 -ffreestanding -Wall -Wextra $(INCLUDES)
CXXFLAGS := -std=c++17 -ffreestanding -Wall -Wextra $(INCLUDES)

BUILD_DIR := build
SRC_DIR := src

CSOURCES := \
    data.c \
    hello.c

CXXSOURCES :=

OBJS=$(CSOURCES:%.c=$(BUILD_DIR)/%.c.o) $(CXXSOURCES:%.cpp=$(BUILD_DIR)/%.cpp.o)

.PHONY: all run clean
.SUFFIXES: .o .c

all: moss.iso

moss.iso: $(OBJS)
	$(CC) -nostdlib -Wl,-dll -shared -Wl,--subsystem,10 -e efi_main -o $(BUILD_DIR)/BOOTX64.EFI $(OBJS)
	dd if=/dev/zero of=$(BUILD_DIR)/fat.img bs=1k count=1440
	mformat -i $(BUILD_DIR)/fat.img -f 1440 ::
	mmd -i $(BUILD_DIR)/fat.img ::/EFI
	mmd -i $(BUILD_DIR)/fat.img ::/EFI/BOOT
	mcopy -i $(BUILD_DIR)/fat.img $(BUILD_DIR)/BOOTX64.EFI ::/EFI/BOOT
	mkdir -p iso
	cp $(BUILD_DIR)/fat.img iso
	xorriso -as mkisofs -R -f -e fat.img -no-emul-boot -o moss.iso iso

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	qemu-system-x86_64 -L .. -pflash $(OVMF_DIR)/OVMF.fd -cdrom moss.iso

clean:
	rm -rf $(BUILD_DIR)
	rm -rf iso
