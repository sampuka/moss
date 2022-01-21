#include "uefi_con.h"

//extern "C" {

int kernel_main()
{
    uefi_conout_outputstring(u"Hello from kernel!!\r\n");
    return 0;
}

//} // extern "C"
