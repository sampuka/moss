#include <efi.h>
#include <efilib.h>

#include "uefi_con.h"
#include "uefi_gop.h"

#include "kernel_main.h"

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    // Store the system table for future use in other functions
    ST = SystemTable;
    BS = SystemTable->BootServices;
    //RT = SystemTable->RuntimeServices;

    //InitializeLib(ImageHandle, SystemTable);

    // Say hi
    uefi_conout_outputstring(u"Hello Moss!\r\n");

    // Initialize GOP
    uefi_conout_outputstring(u"Initializing GOP... ");

    int gop_status = uefi_gop_init();

    if (gop_status)
    {
        uefi_conout_outputstring(u"failed\r\n");
    }
    else
    {
        uefi_conout_outputstring(u"succes\r\n");
    }

    // Flush keystroke buffer
    uefi_conin_reset();

    // Wait for keystroke
    uint16_t c = 0;
    while (uefi_conin_readkeystroke(&c) || 1)
        ;

    /*
    // Locate GOP
    EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;

    EFI_STATUS gop_status = BS->LocateProtocol(&gop_guid, NULL, (void**)&gop);
    */

    int main_status = kernel_main();

    if (main_status == 0)
    {
        return EFI_SUCCESS;
    }
    else
    {
        return EFI_LOAD_ERROR;
    }
}
