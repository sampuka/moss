#include "uefi_con.h"
#include "uefi_gop.h"

extern "C" {

int kernel_main()
{
    uefi_conout_outputstring(u"Hello from kernel!!\r\n");

    const size_t desired_hoz_res = 1280;
    const size_t desired_ver_res = 1280;

    for (size_t i = 0; i < GOP_mode_count; i++)
    {
        const GOPModeInfo *mode_info = &GOP_modes[i];

        if (mode_info->info->HorizontalResolution == desired_hoz_res &&
            mode_info->info->VerticalResolution == desired_ver_res)
        {
            int status = uefi_gop_setmode(i);

            if (status == 0)
            {
                uefi_conout_outputstring(u"Succeeded setting video mode\r\n");
            }
            else
            {
                uefi_conout_outputstring(u"Failed setting video mode\r\n");
            }

            break;
        }
    }


    return 0;
}

} // extern "C"
