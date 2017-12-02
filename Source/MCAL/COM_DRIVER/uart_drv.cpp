#include "uart_drv.h"
#include <msp430.h>

/*Initializing or reconfiguring the eUSCI_A module
 The recommended eUSCI_A initialization/reconfiguration process is:
 1. Set UCSWRST (BIS.B
 #UCSWRST,&UCAxCTL1).
 2. Initialize all eUSCI_A registers with UCSWRST = 1 (including UCAxCTL1).
 3. Configure ports.
 4. Clear UCSWRST through software (BIC.B
 #UCSWRST,&UCAxCTL1).
 5. Enable interrupts (optional) through UCRXIE or UCTXIE.*/

/* UART RX : USCI_A0 PIN 4.3
 * UART TX : USCI_AI PIN 3.4
 *
 * */
void UartDrv::Init(void)
{
    /* Configure PIN 4.3 as RX UART */
    P4SEL1 &= ~(1 << 3);
    P4SEL0 |= (1 << 3);

}

