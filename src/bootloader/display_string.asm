[bits 32]

VIDEO_MEMORY equ 0x0b8000
WHITE_ON_BLACK equ 0x0f

display_string:
    enter 0, 0
    mov edx, VIDEO_MEMORY
    mov ebx, [ebp+8]

    display_string_loop:
        mov al, [ebx]

        cmp al, 0
        je display_string_end

        mov ah, WHITE_ON_BLACK
        mov [edx], ax

        add edx, 2
        add ebx, 1

        jmp display_string_loop

    display_string_end:
    leave
    ret 4
