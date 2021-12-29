; For printing a number as hex using the BIOS ISR
; Expects two byte pushed on the stack
; No guarantee of preserving register values

bios_print_hex1:
enter 0, 0

mov bl, [bp+4]
shr bl, 4
mov byte cl, [hex1_template_format_string+2]
mov byte [hex1_format_string+2], cl
add byte [hex1_format_string+2], bl

mov bl, [bp+4]
and bl, 0x0f
mov byte cl, [hex1_template_format_string+3]
mov byte [hex1_format_string+3], cl
add byte [hex1_format_string+3], bl

mov bx, 2
bios_print_hex1_fix_loop:
cmp byte [hex1_format_string+bx], '9'
jg bios_print_hex1_fix
bios_print_hex1_fix_end:
add bx, 1
cmp bx, 4
je bios_print_hex1_end
jmp bios_print_hex1_fix_loop

bios_print_hex1_fix:
sub byte [hex1_format_string+bx], '9'
add byte [hex1_format_string+bx], '@'
jmp bios_print_hex1_fix_end

bios_print_hex1_end:

push hex1_format_string
call bios_print_string

leave
ret 2


hex1_format_string:
db "0x00",0

hex1_template_format_string:
db "0x00",0
