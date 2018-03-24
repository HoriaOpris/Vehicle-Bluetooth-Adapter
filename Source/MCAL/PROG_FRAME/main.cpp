#include "../IO_DRIVER/port_drv.h"
#include "../UC_DRIVER/watchdog_drv.h"
#include "../COM_DRIVER/uart_drv.h"

void main(void)
{
    WatchDog watchdog;
    watchdog.StopWatchdog();

    PortDriver Pin_0(PIN_0);
    PortDriver Pin_6(PIN_6);
    PortDriver Pin_2(PIN_2);

    Pin_0.Configure(DIR_OUTPUT);
    Pin_6.Configure(DIR_OUTPUT);
    Pin_2.Configure(DIR_INPUT);

    //UartDrv uart;

    //uart.Init();

    while (true)
    {
        Pin_0.Output(OUT_TOGGLE);

        if (Pin_2.Input() == IN_HIGH)
        {
            Pin_6.Output(OUT_TOGGLE);
        }

        // delay for a while
        for (volatile int i = 0; i < 0xF000; i++)
        {
            ;
        }
    }
}
