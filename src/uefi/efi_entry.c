#include <efi.h>
#include <efilib.h>

#include "uefi/uefi_con.h"
#include "uefi/uefi_gop.h"

#include "kernel/kernel_main.h"

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

    uefi_conout_outputstring(u"Init finished. Press any key to continue...\r\n");

    // Flush keystroke buffer
    uefi_conin_reset();

    // Wait for keystroke
    uint16_t c = 0;
    while (uefi_conin_readkeystroke(&c))
    {
        ;
    }

    int main_status = kernel_main();

    uefi_conout_outputstring(u"UEFI program ended. Press any key to return to shell...\r\n");

    // Flush keystroke buffer
    uefi_conin_reset();

    // Wait for keystroke
    c = 0;
    while (uefi_conin_readkeystroke(&c))
    {
        ;
    }

    if (main_status == 0)
    {
        return EFI_SUCCESS;
    }
    else
    {
        return EFI_LOAD_ERROR;
    }
}
