[bits 16]

switch_to_protected_mode:
    cli ; Make sure no interrupts happens until we can safely reenable them

    lgdt [gdt_descriptor] ; Load GDT

    ; Set the first bit of cr0 to enable protected mode
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp CODE_SEGMENT:init_protected_mode


[bits 32]

init_protected_mode:
    mov ax, DATA_SEGMENT
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x090000 ; Update stack position so it is right at the top of the free space
    mov esp, ebp

    call begin_protected_mode
