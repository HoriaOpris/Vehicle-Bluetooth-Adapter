#include "watchdog_drv.h"
#include <msp430.h>

void WatchDog::StopWatchdog(void)
{
    WDTCTL = WDTPW | WDTHOLD; /* Stops the watch-dog timer. */
    PMMCTL0 = PMMPW; /* Opens PMM Module. */
    PM5CTL0 &= ~LOCKLPM5; /* Clears locked Input output pins. */
}
