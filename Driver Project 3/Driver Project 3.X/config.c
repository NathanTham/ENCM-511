/*
 * File:   config.c
 * Author: Nathan
 *
 * Created on October 23, 2021, 5:52 PM
 */

#include "xc.h"

void Config()
{
    INTCON1bits.NSTDIS = 1; // Disable interrupt nesting
    
    IPC4bits.CNIP = 111;    // Give external interrupts priority level 7
    IPC1bits.T2IP = 110;    // Give Timer 2 priority level 6
    
    IFS1bits.CNIF = 0;      // Clear input interrupt flag
    IFS0bits.T2IF = 0;      // Clear Timer 2 flag
    
    IEC1bits.CNIE = 1;      // Input interrupt enabled
    IEC0bits.T2IE = 1;      // Timer 2 Interrupt enabled
    CNEN1bits.CN0IE = 1;    // Input CN0 (RA4) interrupt enabled
    CNEN1bits.CN1IE = 1;    // Input CN1 (RB4) interrupt enabled
    CNEN2bits.CN30IE = 1;   // Input CN30 (RA2) interrupt enabled
    
    Disp2String("\r Nothing pressed        ");
    
    // Set clock
    NewClk(32); // Set clock to 32kHz to reduce power consumption 
    
    return;    
}


