# Moss

Moss is an ambitious attempt to create an OS of some degree.

Current implementation heavily relying on [UEFI App Bare Bones - OSDev Wiki](https://wiki.osdev.org/UEFI_App_Bare_Bones)

# Dependencies

Setup is based on the osdev.org article.  
`sudo apt install qemu ovmf gnu-efi binutils-mingw-w64 gcc-mingw-w64 xorriso mtools`

After installing omvf, you need to copy this file to the repository  
`cp /usr/share/ovmf/OVMF.fd .`

# Progress

- [x] Decide to scrap legacy BIOS approach in favor of UEFI

- [x] UEFI loadable kernel code

- [ ] Graphics mode driver

- [ ] Fancy splash screen

- [ ] Keyboard driver

- [ ] The most basic terminal environment imaginable

- [ ] Pong!

- [ ] ???

- [ ] Profit!
