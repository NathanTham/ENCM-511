/*
 * File:   gpio.c
 * Author: Nathan
 *
 * Created on November 13, 2021, 4:34 PM
 */

#include "xc.h"

int PB1 = 0; //RA2
int PB2 = 0; //RA4
int PB3 = 0; //RB4

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void)
{   
    //Set initial PB values
    PB1 = 0;
    PB2 = 0;
    PB3 = 0;
    
    //Set PB1, PB2 & PB3 as on when pushbutton pressed 
    
    Delay_ms(100);
    if(PORTAbits.RA2 == 0)
    {
        PB1 = 1;
    }
    if(PORTAbits.RA4 == 0)
    {
        PB2 = 1; 
    }
    if(PORTBbits.RB4 == 0)
    {
        PB3 = 1; 
    }
    IFS1bits.CNIF = 0;
    Nop();
}
