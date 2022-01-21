#ifndef UEFI_UTILS
#define UEFI_UTILS

#include <efi.h>
#include <efilib.h>

uint16_t* uefi_utils_status_string(EFI_STATUS status);

#endif
