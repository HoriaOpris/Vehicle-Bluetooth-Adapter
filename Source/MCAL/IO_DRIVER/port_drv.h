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
    PIN_0 = 0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7,
};
enum PinDirection
{
    DIR_INPUT,
    DIR_OUTPUT
};

enum PinOutput
{
    OUT_HIGH,
    OUT_LOW
};

class PortDriver
{
public:
    PortDriver(enum PinNumber pin);
    void Init(void);
    void Output(enum PinOutput out);
    void Configure(enum PinDirection dir);

private:
    uint8_t PortDrv_pin;

    void StopWatchdog(void);
};

#endif /* SOURCE_MCAL_PORT_DRV_H_ */
