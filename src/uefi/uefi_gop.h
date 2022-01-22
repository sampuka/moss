#ifndef UEFI_GOP
#define UEFI_GOP

#include <efi.h>
#include <efilib.h>

#define GOP_MAX_MODES_SUPPORTED 100

typedef struct
{
    UINTN SizeOfInfo;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *info;
} GOPModeInfo;

extern GOPModeInfo GOP_modes[GOP_MAX_MODES_SUPPORTED];
extern UINTN GOP_mode_count;
extern UINTN GOP_active_mode;

#ifdef __cplusplus
extern "C" {
#endif

int uefi_gop_init();
int uefi_gop_setmode(UINTN mode);

#ifdef __cplusplus
}
#endif

#endif
