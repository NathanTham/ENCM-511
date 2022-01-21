/*
 * File:   gpio.c
 * Author: Nathan
 *
 * Created on October 23, 2021, 5:52 PM
 */

#include "xc.h"
#include "timers.h"
#include "IO.h"

int PB1 = 0; //RA2
int PB2 = 0; //RA4
int PB3 = 0; //RB4

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void)
{
    IFS1bits.CNIF = 0;
    Nop();
    
    NewClk(8); //Set clock to 8MHz (Speed up clock after input is registered)
    
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
   
}
