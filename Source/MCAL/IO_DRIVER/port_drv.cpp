/*
 * port_drv.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: Horia Opris
 */
#include "port_drv.h"
#include <msp430.h>

PortDriver::PortDriver(enum PinNumber pin)
{
    if ((pin >= PIN_0) && (pin <= PIN_7))
    {
        PortDrv_pin = (uint8_t) pin;
    }
    else
    {
        /* TODO @Horia: Error hook */
    }

}

void PortDriver::Configure(enum PinDirection dir)
{
    switch (dir)
    {
        case DIR_INPUT:
            P1DIR &= ~BitForCurrentPin();
            break;

        case DIR_OUTPUT:
            P1DIR |= BitForCurrentPin();
            break;

        default:
            break;
    }
}

void PortDriver::Output(enum PinOutput out)
{
    switch (out)
    {
        case OUT_HIGH:
            P1OUT |= BitForCurrentPin();
            break;

        case OUT_LOW:
            P1OUT &= ~BitForCurrentPin();
            break;

        case OUT_TOGGLE:
            P1OUT ^= BitForCurrentPin();
            break;
    }
}

uint8_t PortDriver::BitForCurrentPin(void)
{
    return (1 << PortDrv_pin);
}
