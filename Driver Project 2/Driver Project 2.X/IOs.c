/*
 * File:   IOs.c
 * Author: Nathan
 *
 * Created on October 12, 2021, 2:55 PM
 */

#include <xc.h>
#include <p24fxxxx.h>
#include <p24F16KA101.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>

#include "xc.h"
#include "TimeDelay.h"

void IOinit(void) {
   
    //Inputs
    TRISAbits.TRISA2 = 1; //Button 1
    TRISAbits.TRISA4 = 1; //Button 2
    TRISBbits.TRISB4 = 1; //Button 3
    
    //PullUp 
    CNPU2bits.CN30PUE = 1;
    CNPU1bits.CN0PUE = 1;
    CNPU1bits.CN1PUE = 1;
    
    //Outputs
    TRISBbits.TRISB8 = 0; //LED
    
    AD1PCFG = 0xFFFF; //Turn all analog pins as digital 
       
    return;
}

//Change of pin Interrupt subroutine
void __attribute__ ((interrupt, no_auto_psv)) _CNInterrupt(void) {
    //ChangeClk(8);
    IFS1bits.CNIF = 0; //clear IF flag
    Nop();
        if(PORTAbits.RA2 == 0)
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
        else
        {
            LATBbits.LATB8 = 0; 
        }
}
