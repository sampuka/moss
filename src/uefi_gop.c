#include "uefi_gop.h"

#include <efi.h>
#include <efilib.h>

#include "uefi_con.h"

EFI_GUID gop_guid;
EFI_GRAPHICS_OUTPUT_PROTOCOL *gop = NULL;

EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *info = NULL;
UINTN SizeOfInfo = 0;
UINTN numModes = 0;
UINTN nativeMode = 0;

int uefi_gop_init()
{
    uefi_conout_outputstring(u".");
    EFI_STATUS Status = BS->LocateProtocol(&gop_guid, NULL, (void**)&gop);
    uefi_conout_outputstring(u".");

    if (EFI_ERROR(Status))
    {
        for (int i = 1; i < Status; i*=2)
        {
            uefi_conout_outputstring(u".");
        }
        return 1;
    }

    uefi_conout_outputstring(u".");
    Status = gop->QueryMode(gop, gop->Mode==NULL?0:gop->Mode->Mode, &SizeOfInfo, &info);
    uefi_conout_outputstring(u".");

    // this is needed to get the current video mode
    if (Status == EFI_NOT_STARTED)
    {
        uefi_conout_outputstring(u".");
        Status = gop->SetMode(gop, 0);
        uefi_conout_outputstring(u".");
    }

    if(EFI_ERROR(Status))
    {
        return 1;
    }
    else
    {
        nativeMode = gop->Mode->Mode;
        numModes = gop->Mode->MaxMode;
    }

    return 0;
}
