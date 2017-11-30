#include "../IO_DRIVER/port_drv.h"

/**
 * main.c
 */
void main(void)
{
    PortDrv_Init();

    while (true)
    {
        PortDrv_Main();
    }
}
