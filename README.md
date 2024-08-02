# Moss

Moss is an ambitious attempt to create an OS of some degree.

Current implementation heavily relying on [UEFI App Bare Bones - OSDev Wiki](https://wiki.osdev.org/UEFI_App_Bare_Bones)

# Dependencies

This list is from above link. However I installed and built gnu-efi manually so I could have `/lib/data.c` (which also needs to be modified as described by above link), which doesn't seem to come with the Ubuntu package.
It also has some instructions to install `mkgpt`.

`sudo apt-get install qemu ovmf gnu-efi gcc-mingw-w64 xorriso mtools`

Maybe needed (it can be a bit hard to keep track):  
`sudo apt-get install binutils-mingw-w64`

# Progress

- [x] Decide to scrap legacy BIOS approach in favor of UEFI

- [x] UEFI loadable kernel code

- [ ] Graphics mode driver

- [ ] Fancy splash screen

- [ ] Keyboard driver

- [ ] The most basic terminal environment imaginable

- [ ] Pong!

- [ ] 

- [ ] TBD
