#include "../IO_DRIVER/port_drv.h"
#include "../UC_DRIVER/watchdog_drv.h"
#include "../COM_DRIVER/uart_drv.h"

#include <msp430.h>

enum taskSymbol
{
    TASK_1_MS,
    TASK_5_MS,
    TASK_10_MS,
    TASK_25_MS,
    TASK_TOTAL
};

PortDriver Pin_0(PIN_0, DIR_OUTPUT);

typedef void (*FP)(void);

struct RTOS
{
    unsigned count;
    const unsigned div;
    const FP task;
};

static void Task_1_ms(void)
{
    Pin_0.Output(OUT_TOGGLE);
}

static void Task_5_ms(void)
{
    Pin_0.Output(OUT_TOGGLE);
}

static void Task_10_ms(void)
{
    Pin_0.Output(OUT_TOGGLE);
}

static void Task_25_ms(void)
{
    Pin_0.Output(OUT_TOGGLE);
}

static struct RTOS rtos[TASK_TOTAL] = { { 0, 1, Task_1_ms },
        { 0, 5, Task_5_ms }, { 0, 10, Task_10_ms }, { 0, 25, Task_25_ms } };

static void Rtos(void)
{
    for( unsigned i = 0; i < TASK_TOTAL; i++)
    {
        if (rtos[i].count >= rtos[i].div)
        {
            rtos[i].count = 0;

            rtos[i].task();
        }
    }
}

static void timerA_cfg(void)
{
    const unsigned ticks_for_1_ms_when_frq_1_mhz = 1000;

    TA0CTL = TASSEL__SMCLK | MC__UP;
    TA0CCR0 = ticks_for_1_ms_when_frq_1_mhz;

    /* Enable interrupts */
    TA0CCTL0 = CCIE;
    __enable_interrupt();
}

void main(void)
{
    WatchDog watchdog;
    watchdog.StopWatchdog();

    PortDriver Pin_2(PIN_2, DIR_INPUT);
    PortDriver Pin_6(PIN_6, DIR_OUTPUT);

    //UartDrv uart;
    //uart.Init();

    timerA_cfg();

    while (1)
        Rtos();
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    for( unsigned i = 0; i < TASK_TOTAL; i++)
    {
        rtos[i].count++;
    }

    TA0CTL &= ~1;
}
