; For printing a number as hex using the BIOS ISR
; Expects two bytes pushed on the stack
; No guarantee of preserving register values

bios_print_hex2:
enter 0, 0

mov bl, [bp+5]
shr bl, 4
mov cl, [hex2_template_format_string+2]
mov byte [hex2_format_string+2], cl
add byte [hex2_format_string+2], bl

mov bl, [bp+5]
and bl, 0x0f
mov byte cl, [hex2_template_format_string+3]
mov byte [hex2_format_string+3], cl
add byte [hex2_format_string+3], bl

mov bl, [bp+4]
shr bl, 4
mov byte cl, [hex2_template_format_string+4]
mov byte [hex2_format_string+4], cl
add byte [hex2_format_string+4], bl

mov bl, [bp+4]
and bl, 0x0f
mov byte cl, [hex2_template_format_string+5]
mov byte [hex2_format_string+5], cl
add byte [hex2_format_string+5], bl

mov bx, 2
bios_print_hex2_fix_loop:
cmp byte [hex2_format_string+bx], '9'
jg bios_print_hex2_fix
bios_print_hex2_fix_end:
add bx, 1
cmp bx, 6
je bios_print_hex2_end
jmp bios_print_hex2_fix_loop

bios_print_hex2_fix:
sub byte [hex2_format_string+bx], '9'
add byte [hex2_format_string+bx], '@'
jmp bios_print_hex2_fix_end

bios_print_hex2_end:

push hex2_format_string
call bios_print_string

leave
ret 2


hex2_format_string:
db "0x0000",0

hex2_template_format_string:
db "0x0000",0
