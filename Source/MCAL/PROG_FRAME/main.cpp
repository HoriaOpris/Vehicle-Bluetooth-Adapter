#include "../IO_DRIVER/port_drv.h"

/**
 * main.c
 */
void main(void)
{
    PortDriver Port;

    Port.Init();

    while (true)
    {
        Port.Run();
    }
}
