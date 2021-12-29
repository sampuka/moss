[org 0x7c00]

mov [boot_drive], dl ; BIOS stores boot drive in dl, best to save it for later

mov bp, 0x8000
mov sp, bp

push boot_message
call bios_print_string

;push 0x80 ; Drive to load from (0x00 for floppy, 0x80 for hdd)
;push 0x00 ; Cylinder
;push 0x00 ; Head
;push 0x02 ; Sector (1-indexed)
;push 0x04 ; Sectors to read
;push 0x9000 ; Destination
;call bios_disk_load

;push word [0x9000]
;call bios_print_hex2

;push word [0x9000+512]
;call bios_print_hex2

;push word [0x9000+1024]
;call bios_print_hex2

;push word [0x9000+1536]
;call bios_print_hex2

call switch_to_protected_mode ; Switch to protected mode, will never return here

jmp $ ; Jump here, infinite loop

%include "bios_print_string.asm"
;%include "bios_print_hex1.asm"
;%include "bios_print_hex2.asm"
;%include "bios_disk_load.asm"

%include "display_string.asm"
%include "switch_to_protected_mode.asm"
%include "gdt.asm"
%include "print_string.asm"

[bits 32]
begin_protected_mode:

;push boot_message
;push protected_mode_message
;call display_string

mov ebx, protected_mode_message
call print_string_pm

mov ecx, 0xaaaa5555

jmp $ ; Hang forever

boot_drive:
db byte 0

boot_message db `\nHello Moss!\r\n`,0
protected_mode_message db `Entered protected mode!`,0

times 510-($-$$) db 0 ; Zero-fill until 510th byte

dw 0xaa55 ; Set the last two bytes as magic boot sector bytes
times 256 dw 0xdada
times 256 dw 0xface
times 256 dw 0xdead
times 2560 dw 0xbeef
