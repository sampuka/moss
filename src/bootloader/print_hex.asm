; For printing a number as hex using the BIOS ISR
; Expects two bytes pushed on the stack
; No guarantee of preserving register values

print_hex:
enter 0, 0

mov bl, [bp+5]
shr bl, 4
add byte [hex_format_string+2], bl

mov bl, [bp+5]
and bl, 0x0f
add byte [hex_format_string+3], bl

mov bl, [bp+4]
shr bl, 4
add byte [hex_format_string+4], bl

mov bl, [bp+4]
and bl, 0x0f
add byte [hex_format_string+5], bl

mov bx, 2
print_hex_fix_loop:
cmp byte [hex_format_string+bx], '9'
jg print_hex_fix
print_hex_fix_end:
add bx, 1
cmp bx, 6
je print_hex_end
jmp print_hex_fix_loop

print_hex_fix:
sub byte [hex_format_string+bx], '9'
add byte [hex_format_string+bx], '@'
jmp print_hex_fix_end

print_hex_end:

push hex_format_string
call print_string

leave
ret 2


hex_format_string:
db "0x0000",0
