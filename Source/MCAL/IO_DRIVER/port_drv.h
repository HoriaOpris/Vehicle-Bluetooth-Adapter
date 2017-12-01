/*
 * port_drv.h
 *
 *  Created on: Nov 30, 2017
 *      Author: Horia Opris
 */

#ifndef SOURCE_MCAL_PORT_DRV_H_
#define SOURCE_MCAL_PORT_DRV_H_

#include <stdint.h>

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
    PortDriver(uint8_t pin);
    void Init(void);
    void Output(enum PinOutput out);
    void Configure(enum PinDirection dir);

private:
    uint8_t PortDrv_pin;

    void StopWatchdog(void);
};

#endif /* SOURCE_MCAL_PORT_DRV_H_ */
