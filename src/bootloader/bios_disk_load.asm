; For loading disk storage into memory using BIOS ISR
; Expects parameter stack of:
; Byte 11:12 = drive
; Byte 7:10  = cylinder
; Byte 6:8   = head
; Byte 4:5   = sector
; Byte 2:3   = sectors to read
; Byte 0:1   = destination
; No guarantee of preserving register values

bios_disk_load:
enter 0, 0

mov dl, [bp+14] ; Drive
mov ch, [bp+12] ; Cylinder to read from
mov dh, [bp+10] ; Head to read from
mov cl, [bp+8] ; Sector to read from
mov al, [bp+6] ; Sectors to read
mov bx, [bp+4] ; Destination

mov ah, 0x02 ; Prepare ISR for read sector function
int 0x13

jc bios_disk_load_error

cmp al, [bp+6] ; Check the amount of actual read sectors
jne bios_disk_load_error

bios_disk_load_end:

leave
ret 12

bios_disk_load_error:
push word ax
push bios_disk_load_error_msg
call bios_print_string
call bios_print_hex1
jmp bios_disk_load_end

bios_disk_load_error_msg:
db `Disk load error: `,0
