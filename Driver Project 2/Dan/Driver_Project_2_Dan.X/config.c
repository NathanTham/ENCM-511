/*
 * File:   config.c
 * Author: dan.tran2
 *
 * Created on October 15, 2021, 7:39 PM
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
    
    // Change Clock
    NewClk(32); // Set clock to 32kHz to reduce power consumption 
    
    return;    
}

