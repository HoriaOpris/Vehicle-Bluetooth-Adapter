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
    // stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD; /* Stops the watch-dog timer. */
    PMMCTL0 = PMMPW; /* Opens PMM Module. */
    PM5CTL0 &= ~LOCKLPM5; /* Clears locked Input output pins. */

    // set up bit 0 of P1 as output
    P1DIR = 0x01;

    // intialize bit 0 of P1 to 0

    P1OUT = 0x00;
}

void PortDriver::Run(void)
{
    volatile int i;

    // toggle bit 0 of P1

    P1OUT ^= 0x01;

    // delay for a while

    for (i = 0; i < 0x6000; i++)
        ;
}
