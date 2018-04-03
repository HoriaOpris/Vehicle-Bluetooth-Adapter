#include "../IO_DRIVER/port_drv.h"
#include "../UC_DRIVER/watchdog_drv.h"
#include "../COM_DRIVER/uart_drv.h"
#include "../../KERNEL/kernel.h"
#include "../LCD_DRIVER/lcd_drv.h"

void main(void)
{
    WatchDog watchdog;
    watchdog.StopWatchdog();

    PortDriver Pin_2(PIN_2, DIR_INPUT);
    PortDriver Pin_6(PIN_6, DIR_OUTPUT);

    //UartDrv uart;
    //uart.Init();

    Rtos rtos;

    Init_LCD();



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
