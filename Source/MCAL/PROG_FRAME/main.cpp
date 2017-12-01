#include "../IO_DRIVER/port_drv.h"
#include "../UC_DRIVER/watchdog_drv.h"
#include "../COM_DRIVER/uart_drv.h"

void main(void)
{
    WatchDog watchdog;
    watchdog.StopWatchdog();

    PortDriver Pin_0(PIN_0);
    PortDriver Pin_6(PIN_6);

    Pin_0.Configure(DIR_OUTPUT);
    Pin_6.Configure(DIR_OUTPUT);

    UartDrv uart;

    uart.Init();

    while (true)
    {
        Pin_0.Output(OUT_TOGGLE);
        Pin_6.Output(OUT_TOGGLE);

        // delay for a while
        for (volatile int i = 0; i < 0xF000; i++)
        {
            ;
        }
    }
}
