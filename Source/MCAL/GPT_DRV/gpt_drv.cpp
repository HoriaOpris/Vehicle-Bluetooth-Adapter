#include "gpt_drv.h"
#include <msp430.h>

void GptDriver::Configure(void)
{
    TA1CCR0 = 200;
    TA1CCTL2 |= OUTMOD_7;
    TA1CCR2 = 100;
    TA1CTL = TASSEL__SMCLK | MC__UP;
}
