/*
 * File:   config.c
 * Author: Nathan
 *
 * Created on November 13, 2021, 4:28 PM
 */

#include "xc.h"

void Config()
{
    TRISAbits.TRISA2 = 1;   // Set RA2 as input (B1)
    TRISAbits.TRISA4 = 1;   // Set RA4 as input (B2)
    TRISBbits.TRISB4 = 1;   // Set RB4 as input (B3)
    
    AD1PCFG = 0xFFFF;
    
    TRISAbits.TRISA3 = 1;   // Set RA3 as input (pot)
    AD1PCFGbits.PCFG5 = 0;      //Configure AN5 in Analog mode
    
    CNPU2bits.CN30PUE = 1;  // RA2 Pull up
    CNPU1bits.CN0PUE = 1;   // RA4 Pull up
    CNPU1bits.CN1PUE = 1;   // RB4 Pull up
    
    IPC4bits.CNIP = 111;    // Give CN interrupts priority level 7 (Highest)
    IPC1bits.T2IP = 110;    // Give Timer 2 priority level 6
    
    IFS1bits.CNIF = 0;      // Clear input interrupt flag
    IFS0bits.T2IF = 0;      // Clear Timer 2 flag
    
    IEC1bits.CNIE = 1;      // Input CN interrupt enabled
    IEC0bits.T2IE = 1;      // Timer 2 Interrupt enabled
    CNEN1bits.CN0IE = 1;    // Input CN0 (RA4) interrupt enabled
    CNEN1bits.CN1IE = 1;    // Input CN1 (RB4) interrupt enabled
    CNEN2bits.CN30IE = 1;   // Input CN30 (RA2) interrupt enabled
    
    Disp2String("\r Nothing pressed        ");
    
    return; 
}