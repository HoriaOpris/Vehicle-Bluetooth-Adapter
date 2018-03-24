/*
 * port_drv.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: Horia Opris
 */
#include "port_drv.h"
#include <msp430.h>

PortDriver::PortDriver(enum PinNumber pin, enum PinDirection dir)
{
    if ((pin >= PIN_0) && (pin <= PIN_7))
    {
        PortDrv_pin = (uint8_t) pin;

        Configure(dir);
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
        P1DIR &= ~CurrentPin();
        P1OUT |= CurrentPin();
        P1REN |= CurrentPin();
        break;

    case DIR_OUTPUT:
        P1DIR |= CurrentPin();
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
        P1OUT |= CurrentPin();
        break;

    case OUT_LOW:
        P1OUT &= ~CurrentPin();
        break;

    case OUT_TOGGLE:
        P1OUT ^= CurrentPin();
        break;
    }
}

bool PortDriver::InputIsHigh(void)
{
    if ((P1IN & CurrentPin()) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

uint8_t PortDriver::CurrentPin(void)
{
    return (1 << PortDrv_pin);
}
