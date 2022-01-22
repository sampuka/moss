#ifndef UEFI_GOP
#define UEFI_GOP

#include <efi.h>
#include <efilib.h>

#define GOP_MAX_MODES_SUPPORTED 50

typedef struct
{
    UINTN SizeOfInfo;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *info;
} GOPModeInfo;

extern GOPModeInfo GOP_modes[GOP_MAX_MODES_SUPPORTED];

extern UINTN GOP_mode_count;

int uefi_gop_init();

#endif
