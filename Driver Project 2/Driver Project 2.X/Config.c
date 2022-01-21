/*
 * File:   Config.c
 * Author: Natha
 *
 * Created on October 16, 2021, 2:45 PM
 */


#include "xc.h"

void Config()
{
    INTCON1bits.NSTDIS = 1; // Disable interrupt nesting
    
    IPC4bits.CNIP = 111;    // Set priority of CN interrupt to level 7
    
    IFS1bits.CNIF = 0;      // Clear input interrupt flag
    
    IEC1bits.CNIE = 1;      // Input interrupt enabled (Enable control register 1)
    
    CNEN1bits.CN0IE = 1;    // Input CN0 (RA4) interrupt enabled
    CNEN1bits.CN1IE = 1;    // Input CN1 (RB4) interrupt enabled
    CNEN2bits.CN30IE = 1;   // Input CN30 (RA2) interrupt enabled
    
    return;    
}
