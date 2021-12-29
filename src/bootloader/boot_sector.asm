[org 0x7c00]

push boot_message
call print_string

push 0xee33
call print_hex

jmp $ ; Jump here, infinite loop

%include "print_string.asm"
%include "print_hex.asm"

boot_message:
db `Hello Moss!\n\r`,0

times 510-($-$$) db 0 ; Zero-fill until 510th byte

dw 0xaa55 ; Set the last two bytes as magic boot sector bytes
