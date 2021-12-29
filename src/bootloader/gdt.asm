gdt_start:

gdt_null: ; Mandatory null-descriptor
    dd 0
    dd 0

gdt_code: ; Code segment descriptor
    dw 0xffff    ; Limit
    dw 0x0000    ; Base
    db 0x00      ; Base part 2
    db 10011010b ; Type flags
    db 11001111b ; Limit part 2?
    db 0x00      ; Base part 3

gdt_data: ; Data segment descriptor
    dw 0xffff    ; Limit
    dw 0x0000    ; Base
    db 0x00      ; Base part 2
    db 10010010b ; Type flags
    db 11001111b ; Limit part 2?
    db 0x00      ; Base part 3

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; GDT size
    dd gdt_start               ; GDT start

CODE_SEGMENT equ gdt_code - gdt_start
DATA_SEGMENT equ gdt_data - gdt_start
