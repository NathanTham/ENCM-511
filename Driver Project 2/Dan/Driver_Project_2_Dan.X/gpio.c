/*
 * File:   gpio.c
 * Author: dan.tran2
 *
 * Created on October 15, 2021, 7:39 PM
 */

#include <xc.h>
#include <p24fxxxx.h>
#include <p24F16KA101.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>

#include "xc.h"
#include "timers.h"

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void)
{
    IFS1bits.CNIF = 0;
    Nop();
    
    NewClk(8); //Set clock to 8MHz (Speed up clock after input is registered)
    
    //Check for multiple pushbutton inputs 
    if(!PORTAbits.RA2 && !PORTAbits.RA4) 
        LATBbits.LATB8 = 1;
    else if(!PORTAbits.RA4 && !PORTBbits.RB4)
        LATBbits.LATB8 = 1;
    else if(!PORTAbits.RA2 && !PORTBbits.RB4)
        LATBbits.LATB8 = 1;
    //Check which pushbutton was pressed 
    else if(PORTAbits.RA2 == 0)
    {
        while(PORTAbits.RA2 == 0)
        {
            LATBbits.LATB8 = 1;
            Delay_ms(1000);
            LATBbits.LATB8 = 0;
            Delay_ms(1000);
        }
    }
    else if(PORTAbits.RA4 == 0)
    {
        while(PORTAbits.RA4 == 0)
        {
            LATBbits.LATB8 = 1;
            Delay_ms(2000);
            LATBbits.LATB8 = 0;
            Delay_ms(2000);
        }
    }
    else if(PORTBbits.RB4 == 0)
    {
        while(PORTBbits.RB4 == 0)
        {
            LATBbits.LATB8 = 1;
            Delay_ms(3000);
            LATBbits.LATB8 = 0;
            Delay_ms(3000);
        }
    }
    else //default state
        LATBbits.LATB8 = 0;
        
    NewClk(32); //Slow down clock once interrupt subroutine is finished 
}