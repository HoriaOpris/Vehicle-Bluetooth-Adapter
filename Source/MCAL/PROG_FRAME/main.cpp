#include "../IO_DRIVER/port_drv.h"
#include "../UC_DRIVER/watchdog_drv.h"
#include "../COM_DRIVER/uart_drv.h"

#include <msp430.h>

static void timerA_cfg(void)
{
    // CLock config to ACLK
    TA0CTL |= 1 << 8;
    TA0CTL &= ~(1 << 9);

    //Mode control set to count up to TA0CCR0
    TA0CTL |= 1 << 4;
    TA0CTL &= ~(1 << 5);

    // Value to count up to
    TA0CCR0 = 5000;
}

void main(void)
{
    WatchDog watchdog;
    watchdog.StopWatchdog();

    PortDriver Pin_0(PIN_0, DIR_OUTPUT);
    PortDriver Pin_2(PIN_2, DIR_INPUT);
    PortDriver Pin_6(PIN_6, DIR_OUTPUT);

    //UartDrv uart;
    //uart.Init();

    timerA_cfg();

    while (true)
    {
        if (TA0R == 4950)
            Pin_0.Output(OUT_TOGGLE);
    }
}
