/*
 * kernel.cpp
 *
 *  Created on: Apr 2, 2018
 *      Author: horia
 */

#include "kernel.h"
#include "../MCAL/IO_DRIVER/port_drv.h"
#include <msp430.h>

PortDriver Pin_0(PIN_0, DIR_OUTPUT);
static struct RTOS rtos[TASK_TOTAL] = { { 0, 1, Rtos::Task_1_ms }, { 0, 5,
        Rtos::Task_5_ms }, { 0, 10, Rtos::Task_10_ms }, { 0, 25,
        Rtos::Task_25_ms } };

void Rtos::Run(void)
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

void Rtos::Init(void)
{
    const unsigned ticks_for_1_ms_when_frq_1_mhz = 1000;

    TA0CTL = TASSEL__SMCLK | MC__UP;
    TA0CCR0 = ticks_for_1_ms_when_frq_1_mhz;

    /* Enable interrupts */
    TA0CCTL0 = CCIE;
    __enable_interrupt();
}

void Rtos::Task_1_ms(void)
{

}

void Rtos::Task_5_ms(void)
{

}

void Rtos::Task_10_ms(void)
{

}

void Rtos::Task_25_ms(void)
{
    Pin_0.Output(OUT_TOGGLE);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Rtos::Timer_A(void)
{
    for( unsigned i = 0; i < TASK_TOTAL; i++)
    {
        rtos[i].count++;
    }

    TA0CTL &= ~1;
}
