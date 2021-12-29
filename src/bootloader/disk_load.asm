; For loading disk storage into memory using BIOS ISR
; Expects parameter stack of:
; Byte 11:12 = drive
; Byte 7:10  = cylinder
; Byte 6:8   = head
; Byte 4:5   = sector
; Byte 2:3   = sectors to read
; Byte 0:1   = destination
; No guarantee of preserving register values

disk_load:
enter 0, 0

;push word [bp+14]
;call print_hex2

;push word [bp+12]
;call print_hex2

;push word [bp+10]
;call print_hex2

;push word [bp+8]
;call print_hex2

;push word [bp+6]
;call print_hex2

;push word [bp+4]
;call print_hex2

;mov dl, [bp+14] ; Drive
mov ch, [bp+12] ; Cylinder to read from
mov dh, [bp+10] ; Head to read from
mov cl, [bp+8] ; Sector to read from
mov al, [bp+6] ; Sectors to read
mov bx, [bp+4] ; Destination
mov dl, 0x80
;mov ch, 0x00
;mov dh, 0x00
;mov cl, 0x02
;mov al, 0x02
;mov bx, 0x9000

mov ah, 0x02 ; Prepare ISR for read sector function
int 0x13

jc disk_load_error

cmp al, [bp+6]
jne disk_load_error

disk_load_end:

leave
ret 12

disk_load_error:
push word ax
push disk_load_error_msg
call print_string
call print_hex1
jmp disk_load_end

disk_load_error_msg:
db `Disk load error: `,0
