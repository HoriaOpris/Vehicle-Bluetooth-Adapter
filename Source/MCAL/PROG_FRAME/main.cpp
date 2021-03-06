#include "../IO_DRIVER/port_drv.h"
#include "../UC_DRIVER/watchdog_drv.h"
#include "../COM_DRIVER/uart_drv.h"
#include "../../KERNEL/kernel.h"
#include "../LCD_DRIVER/lcd_drv.h"

#include <msp430.h>

extern int x;

void main(void)
{
    WatchDog watchdog;
    watchdog.StopWatchdog();

    PortDriver Pin_2(PIN_2, DIR_INPUT);
    Init_LCD();

//UartDrv uart;
//uart.Init();

    Rtos rtos;
    rtos.Init();

    while (true)
    {
        rtos.Run();

        showChar('1', 9);
        showChar('9', 5);
        showChar('1', 3);
        showChar('C', 7);

    }
}
