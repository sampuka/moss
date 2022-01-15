#include "uefi_con.h"

#include <efi.h>
#include <efilib.h>

int uefi_conout_outputstring(uint16_t* str)
{
    EFI_STATUS Status = ST->ConOut->OutputString(ST->ConOut, str);
    //EFI_STATUS Status = uefi_call_wrapper(ST->ConOut->OutputString, 1, str);

    return Status != EFI_SUCCESS;
}

int uefi_conin_reset()
{
    EFI_STATUS Status = ST->ConIn->Reset(ST->ConIn, FALSE);

    return Status != EFI_SUCCESS;
}

int uefi_conin_readkeystroke(uint16_t* ch)
{
    EFI_INPUT_KEY Key;
    EFI_STATUS Status = ST->ConIn->ReadKeyStroke(ST->ConIn, &Key);

    *ch = Key.UnicodeChar;

    return Status != EFI_SUCCESS;
}
