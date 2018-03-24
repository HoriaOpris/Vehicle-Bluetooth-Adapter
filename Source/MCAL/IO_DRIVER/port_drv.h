/*
 * port_drv.h
 *
 *  Created on: Nov 30, 2017
 *      Author: Horia Opris
 */

#ifndef SOURCE_MCAL_PORT_DRV_H_
#define SOURCE_MCAL_PORT_DRV_H_

#include <stdint.h>

enum PinNumber
{
    PIN_0 = 0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7,
};
enum PinDirection
{
    DIR_INPUT, DIR_OUTPUT
};

enum PinOutput
{
    OUT_HIGH, OUT_LOW, OUT_TOGGLE
};

enum PinInput
{
    IN_HIGH, IN_LOW
};

class PortDriver
{
private:
    uint8_t PortDrv_pin;

    uint8_t CurrentPin(void);
    void Configure(enum PinDirection dir);
public:
    PortDriver(enum PinNumber pin, enum PinDirection dir);
    void Output(enum PinOutput out);
    PinInput Input(void);
};

#endif /* SOURCE_MCAL_PORT_DRV_H_ */
