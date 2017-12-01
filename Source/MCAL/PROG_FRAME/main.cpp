#include "../IO_DRIVER/port_drv.h"

/**
 * main.c
 */
void main(void)
{
    PortDriver Port;

    Port.Init();
    Port.Configure(((uint8_t) 0x01U), DIR_OUTPUT);

    while (true)
    {
        Port.Run();
    }
}
