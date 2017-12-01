#include "../IO_DRIVER/port_drv.h"

/**
 * main.c
 */
void main(void)
{
    PortDriver Pin_0(PIN_0);
    PortDriver Pin_6(PIN_6);

    Pin_0.Init();
    Pin_6.Init();

    Pin_0.Configure(DIR_OUTPUT);
    Pin_6.Configure(DIR_OUTPUT);

    while (true)
    {
        Pin_0.Output(OUT_LOW);
        Pin_0.Output(OUT_HIGH);

        Pin_6.Output(OUT_LOW);
        Pin_6.Output(OUT_HIGH);
    }
}
