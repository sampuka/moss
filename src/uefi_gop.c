#include "uefi_gop.h"

#include <efi.h>
#include <efilib.h>

#include "uefi_con.h"
#include "uefi_utils.h"

EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
EFI_GRAPHICS_OUTPUT_PROTOCOL *gop = NULL;

EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *info = NULL;
UINTN SizeOfInfo = 0;
UINTN numModes = 0;
UINTN nativeMode = 0;

int uefi_gop_init()
{
    EFI_STATUS Status = BS->LocateProtocol(&gop_guid, NULL, (void**)&gop);

    if (EFI_ERROR(Status))
    {
        uefi_conout_outputstring(u"GOP LocateProtocol failed with status ");
        uefi_conout_outputstring(uefi_utils_status_string(Status));
        uefi_conout_outputstring(u"\r\n");
        return 1;
    }

    Status = gop->QueryMode(gop, gop->Mode==NULL?0:gop->Mode->Mode, &SizeOfInfo, &info);

    // this is needed to get the current video mode
    if (Status == EFI_NOT_STARTED)
    {
        uefi_conout_outputstring(u"QueryMode returned EFI_NOT_STARTED so setting mode 0\r\n");
        Status = gop->SetMode(gop, 0);
    }

    if(EFI_ERROR(Status))
    {
        uefi_conout_outputstring(u"GOP QueryMode or SetMode failed with status ");
        uefi_conout_outputstring(uefi_utils_status_string(Status));
        uefi_conout_outputstring(u"\r\n");
        return 1;
    }
    else
    {
        nativeMode = gop->Mode->Mode;
        numModes = gop->Mode->MaxMode;
    }

    return 0;
}
