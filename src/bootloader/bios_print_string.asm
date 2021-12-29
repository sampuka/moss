; For printing a string using the BIOS ISR
; Expects a string pointer pushed on the stack
; No guarantee of preserving register values

bios_print_string:
enter 0, 0
mov ah, 0x0e ; Prepare the BIOS ISR to use scrolling teletyping
mov bx, [bp+4]
bios_print_string_loop:
mov al, [bx]
cmp al, 0
je bios_print_string_end
int 0x10
add bx, 1
jmp bios_print_string_loop
bios_print_string_end:
leave
ret 2
