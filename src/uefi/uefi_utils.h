#ifndef UEFI_UTILS
#define UEFI_UTILS

#ifdef __cplusplus
extern "C" {
#endif

#include <efi.h>

uint16_t* uefi_utils_status_string(EFI_STATUS status);

#ifdef __cplusplus
}
#endif

#endif
