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

class PortDriver
{
public:
    void Init(void);
    void Run(void);
    void Configure(uint8_t pin, enum PinDirection dir);

private:
    void StopWatchdog(void);
};

#endif /* SOURCE_MCAL_PORT_DRV_H_ */
