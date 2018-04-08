#include "pwm_drv.h"
#include "../GPT_DRV/gpt_drv.h"
#include <msp430.h>

void PwmDriver::Configure(void)
{
    GptDriver timer;
    timer.Configure();

    P1DIR |= BIT3;
    P1SEL0 &= ~BIT3;
    P1SEL0 |= BIT3;
    P1SEL1 &= ~BIT3;
}

void PwmDriver::DutyCycle(unsigned duty)
{
    TA1CCR2 = duty;
}
