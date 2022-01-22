#include "uefi_gop.h"

#include <efi.h>
#include <efilib.h>

#include "uefi_con.h"
#include "uefi_utils.h"

EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
EFI_GRAPHICS_OUTPUT_PROTOCOL *gop = NULL;

EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *info = NULL;
UINTN SizeOfInfo = 0;
UINTN mode_count = 0;
UINTN native_mode = 0;

GOPModeInfo GOP_modes[GOP_MAX_MODES_SUPPORTED] = {{.SizeOfInfo = 0, .info = NULL}};
UINTN GOP_mode_count = 0;

int uefi_gop_init()
{
    EFI_STATUS LocateProtocolStatus = BS->LocateProtocol(&gop_guid, NULL, (void**)&gop);

    switch (LocateProtocolStatus)
    {
        case EFI_SUCCESS:
            uefi_conout_outputstring(u"  - Locating protocol succeeded\r\n");
            break;

        case EFI_INVALID_PARAMETER:
            uefi_conout_outputstring(u"  - Locating protocol failed with status: EFI_INVALID_PARAMETER\r\n");
            return 1;
            break;

        case EFI_NOT_FOUND:
            uefi_conout_outputstring(u"  - Locating protocol failed with status: EFI_NOT_FOUND\r\n");
            return 1;
            break;

        default:
            uefi_conout_outputstring(u"  - Locating protocol failed with unexpected status\r\n");
            return 1;
            break;
    }

    if (gop->Mode == NULL)
    {
        uefi_conout_outputstring(u"  - GOP Mode struct is NULL?\r\n");
        return 1;
    }

    uefi_conout_outputstring(u"  - Available modes: ");
    uefi_conout_outputstring_uint_dec(gop->Mode->MaxMode);
    uefi_conout_outputstring(u"\r\n");

    GOP_mode_count = gop->Mode->MaxMode;
    if (GOP_mode_count > GOP_MAX_MODES_SUPPORTED)
    {
        GOP_mode_count = GOP_MAX_MODES_SUPPORTED;
    }

    for (size_t mode = 0; mode < GOP_mode_count; mode++)
    {
        GOPModeInfo *GOP_mode = &(GOP_modes[mode]);
        EFI_STATUS QueryModeStatus = gop->QueryMode(gop, mode, &(GOP_modes->SizeOfInfo), &(GOP_mode->info));

        switch (QueryModeStatus)
        {
            case EFI_SUCCESS:
                {
                uefi_conout_outputstring(u"  - Mode ");
                uefi_conout_outputstring_uint_dec(mode+1);
                uefi_conout_outputstring(u": ");
                uefi_conout_outputstring_uint_dec(GOP_mode->info->HorizontalResolution);
                uefi_conout_outputstring(u"x");
                uefi_conout_outputstring_uint_dec(GOP_mode->info->VerticalResolution);
                uefi_conout_outputstring(u"\r\n");
                break;
                }

            case EFI_DEVICE_ERROR:
                uefi_conout_outputstring(u"  - Querying mode failed with status: EFI_DEVICE_ERROR\r\n");
                break;

            case EFI_INVALID_PARAMETER:
                uefi_conout_outputstring(u"  - Querying mode failed with status: EFI_INVALID_PARAMETER\r\n");
                break;

            default:
                uefi_conout_outputstring(u"  - Querying mode failed with unexpected status\r\n");
                break;
        }
    }

    return 0;
}
