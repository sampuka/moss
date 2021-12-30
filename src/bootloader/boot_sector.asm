[bits 16]
[org 0x7c00]

KERNEL_OFFSET equ 0x1000 ; Offset at which we have declared the kernel code to start

mov [boot_drive], dl ; BIOS stores boot drive in dl, best to save it for later

mov bp, 0x8000
mov sp, bp

push boot_message
call bios_print_string

push 0x80 ; Drive to load from (0x00 for floppy, 0x80 for hdd)
push 0x00 ; Cylinder
push 0x00 ; Head
push 0x02 ; Sector (1-indexed)
push 0x15 ; Sectors to read
push KERNEL_OFFSET ; Destination
call bios_disk_load

call switch_to_protected_mode ; Switch to protected mode, will never return here

jmp $ ; Jump here, infinite loop

%include "bios_print_string.asm"
;%include "bios_print_hex1.asm"
;%include "bios_print_hex2.asm"
%include "bios_disk_load.asm"

%include "display_string.asm"
%include "switch_to_protected_mode.asm"
%include "gdt.asm"

[bits 32]
begin_protected_mode:

push protected_mode_message
call display_string

call KERNEL_OFFSET; Go to kernel code and never return

jmp $ ; Hang forever

boot_drive:
db byte 0

boot_message db `\nHello Moss!\r\n`,0
protected_mode_message db `Entered protected mode!`,0

times 510-($-$$) db 0 ; Zero-fill until 510th byte

dw 0xaa55 ; Set the last two bytes as magic boot sector bytes
