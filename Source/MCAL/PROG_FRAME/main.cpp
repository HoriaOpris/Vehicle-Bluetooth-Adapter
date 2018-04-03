#include "../IO_DRIVER/port_drv.h"
#include "../UC_DRIVER/watchdog_drv.h"
#include "../COM_DRIVER/uart_drv.h"
#include "../../KERNEL/kernel.h"

void main(void)
{
    WatchDog watchdog;
    watchdog.StopWatchdog();

    PortDriver Pin_2(PIN_2, DIR_INPUT);
    PortDriver Pin_6(PIN_6, DIR_OUTPUT);

    //UartDrv uart;
    //uart.Init();

    Rtos rtos;

    rtos.Init();

    while (true)
        rtos.Run();
}
