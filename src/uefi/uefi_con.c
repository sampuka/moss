#include "uefi_con.h"

#include <efi/efi.h>
#include <efi/efilib.h>

#pragma GCC diagnostic push  // require GCC 4.6
#pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
int uefi_conout_outputstring(const char16_t* str)
{
    EFI_STATUS Status = ST->ConOut->OutputString(ST->ConOut, str);
    //EFI_STATUS Status = uefi_call_wrapper(ST->ConOut->OutputString, 1, str);

    return Status != EFI_SUCCESS;
}
#pragma GCC diagnostic pop

int uefi_conout_outputstring_uint_dec(size_t n)
{
    char16_t fbuf[] = u"00000000000000000000";
    size_t mask =       10000000000000000000ULL;

    if (n == 0)
    {
        return uefi_conout_outputstring(u"0");
    }

    size_t i = 0;
    for (;i < 20; i++)
    {
        size_t d = (n / mask) % 10;
        if (d > 0)
        {
            break;
        }
        mask /= 10;
    }

    size_t o = 0;

    for (; i < 20; i++)
    {
        size_t d = (n / mask) % 10;
        if (d > 0)
        {
            fbuf[o] += d;
        }

        o++;

        mask /= 10;
    }

    fbuf[o] = u'\0';

    return uefi_conout_outputstring(fbuf);
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
