[org 0x7c00]

mov [boot_drive], dl ; BIOS stores boot drive in dl, best to save it for later

mov bp, 0x8000
mov sp, bp

push boot_message
call print_string

push 0x80 ; Drive to load from (0x00 for floppy, 0x80 for hdd)
push 0x00 ; Cylinder
push 0x00 ; Head
push 0x02 ; Sector (1-indexed)
push 0x04 ; Sectors to read
push 0x9000 ; Destination
call disk_load

push word [0x9000]
call print_hex2

push word [0x9000+512]
call print_hex2

push word [0x9000+1024]
call print_hex2

push word [0x9000+1536]
call print_hex2

jmp $ ; Jump here, infinite loop

%include "print_string.asm"
%include "print_hex1.asm"
%include "print_hex2.asm"
%include "disk_load.asm"

boot_drive:
db byte 0

boot_message:
db `\nHello Moss!\n\r`,0

times 510-($-$$) db 0 ; Zero-fill until 510th byte

dw 0xaa55 ; Set the last two bytes as magic boot sector bytes
times 256 dw 0xdada
times 256 dw 0xface
times 256 dw 0xdead
times 2560 dw 0xbeef
