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
//    PortDriver Pin_6(PIN_6, DIR_OUTPUT);

//UartDrv uart;
//uart.Init();

    Rtos rtos;

    Init_LCD();

    rtos.Init();

    P1DIR |= BIT3;
    P1SEL0 &= ~BIT3;
    P1SEL0 |= BIT3;
    P1SEL1 &= ~BIT3;

    TA1CCR0 = 200;
    TA1CCTL2 |= OUTMOD_7;
    TA1CCR2 = 100;
    TA1CTL = TASSEL__SMCLK | MC__UP;

//    P1DIR |= BIT3;
//    P1OUT |= BIT3;


    while (true)
    {
        rtos.Run();

        TA1CCR2 = x;


        showChar('1', 9);
        showChar('9', 5);
        showChar('1', 3);
        showChar('C', 7);

    }
}
