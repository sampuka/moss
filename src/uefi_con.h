#ifndef UEFI_CON
#define UEFI_CON

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int uefi_conout_outputstring(uint16_t* str);
int uefi_conin_reset();
int uefi_conin_readkeystroke(uint16_t* c);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
