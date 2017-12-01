/*
 * port_drv.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: Horia Opris
 */
#include "port_drv.h"
#include <msp430.h>

void PortDriver::Init(void)
{
    StopWatchdog();
}

void PortDriver::Configure(uint8_t pin, enum PinDirection dir)
{
    switch (dir)
    {
        case DIR_INPUT:
            P1DIR &= ~(1 << pin);
            break;

        case DIR_OUTPUT:
            P1DIR |= (1 << pin);
            break;

        default:
            break;
    }
}

void PortDriver::Output(uint8_t pin, enum PinOutput out)
{
    volatile int i;

    switch (out)
    {
        case OUT_HIGH:
            P1OUT |= (1 << pin);
            break;

        case OUT_LOW:
            P1OUT &= ~(1 << pin);
            break;
    }

// delay for a while
    for (i = 0; i < 0x6000; i++)
        ;
}

void PortDriver::StopWatchdog(void)
{
    WDTCTL = WDTPW | WDTHOLD; /* Stops the watch-dog timer. */
    PMMCTL0 = PMMPW; /* Opens PMM Module. */
    PM5CTL0 &= ~LOCKLPM5; /* Clears locked Input output pins. */
}
