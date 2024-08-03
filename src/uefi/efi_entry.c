#include <efi/efi.h>
#include <efi/efilib.h>

#include "uefi/uefi_con.h"
#include "uefi/uefi_gop.h"

#include "kernel/kernel_main.h"

// Pointer to the EFI system table
EFI_SYSTEM_TABLE *ST;

// Pointer to the boot services table
EFI_BOOT_SERVICES *BS;

// Pointer to the runtime services table
EFI_RUNTIME_SERVICES *RT;

void wait_for_keystroke()
{
    // Flush keystroke buffer
    uefi_conin_reset();

    uint16_t c = 0;
    while (uefi_conin_readkeystroke(&c))
    {
        ;
    }
}

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    // Store the system table for future use in other functions
    ST = SystemTable;
    BS = SystemTable->BootServices;
    RT = SystemTable->RuntimeServices;

    // I suppose this isn't needed if I only use gnu-efi for the headers
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

    wait_for_keystroke();

    int main_status = kernel_main();

    uefi_conout_outputstring(u"UEFI program ended. Press any key to return to shell...\r\n");

    wait_for_keystroke();

    if (main_status == 0)
    {
        return EFI_SUCCESS;
    }
    else
    {
        return EFI_LOAD_ERROR;
    }
}
