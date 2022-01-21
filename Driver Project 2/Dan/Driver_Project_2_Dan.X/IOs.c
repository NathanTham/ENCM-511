/*
 * File:   IOs.c
 * Author: dan.tran2
 *
 * Created on October 15, 2021, 8:44 PM
 */


#include "xc.h"

void IOinit()
{
    TRISAbits.TRISA2 = 1; // Set RA2 as input (B1)
    TRISAbits.TRISA4 = 1; // Set RA4 as input (B2)
    TRISBbits.TRISB4 = 1; // Set RB4 as input (B3)
    TRISBbits.TRISB8 = 0; // Set RB8 as output (LED)
    
    CNPU2bits.CN30PUE = 1; // RA2 Pull up
    CNPU1bits.CN0PUE = 1; // RA4 Pull up
    CNPU1bits.CN1PUE = 1; // RB4 Pull up
    
    AD1PCFG = 0xFFFF;
}

void IOcheck() //Not used since pushbutton interrupts has been enabled
{
    if(PORTAbits.RA2 == 0)
        LATBbits.LATB8 = 1;
    if(PORTAbits.RA4 == 0)
        LATBbits.LATB8 = 1;
    if(PORTBbits.RB4 == 0)
        LATBbits.LATB8 = 1;
    else
        LATBbits.LATB8 = 0;
}
