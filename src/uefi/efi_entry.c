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
    uefi_conout_outputstring(u"Initializing GOP...\r\n");

    int gop_status = uefi_gop_init();

    if (gop_status)
    {
        uefi_conout_outputstring(u"GOP init failed\r\n");
    }
    else
    {
        uefi_conout_outputstring(u"GOP init succeeded\r\n");
    }

    int main_status = kernel_main();

    // Flush keystroke buffer
    uefi_conin_reset();

    // Wait for keystroke
    uint16_t c = 0;
    while (uefi_conin_readkeystroke(&c))
        ;

    if (main_status == 0)
    {
        return EFI_SUCCESS;
    }
    else
    {
        return EFI_LOAD_ERROR;
    }
}
