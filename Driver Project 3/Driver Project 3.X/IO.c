/*
 * File:   IO.c
 * Author: Nathan
 *
 * Created on October 23, 2021, 5:53 PM
 */

#include "xc.h"
#include "timers.h"
#include "gpio.h"

int PBstate = 0b000;
extern int PB1; //PB1 from gpio.c
extern int PB2; //PB2 from gpio.c
extern int PB3; //PB3 from gpio.c

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

void IOCheck()
{
    //PB1 : RA2
    //PB2 : RA4
    //PB3 : RB4
    
    //Check if any pushbuttons are pressed
    if(PB1 == 1 || PB2 == 1 || PB3 == 1)
    {
       NewClk(8); //Set clock to 8MHz (Speed up clock after input is registered) 
    }
    
    PBstate = 0b000;
    
    if (PB1 == 1)
    {
        PBstate+=0b001;
    }
    if (PB2 == 1)
    {
        PBstate+=0b010;
    }
    if (PB3 == 1)
    {
        PBstate+=0b100;
    }
 
    switch(PBstate)
    {
        case 0b001:   //PB1 pressed
            Disp2String("\r PB1 is pressed        "); 
            LATBbits.LATB8 = 1;
            Delay_ms(500);
            LATBbits.LATB8 = 0;
            Delay_ms(500);
            break;
        case 0b010:   //PB2 pressed
            Disp2String("\r PB2 is pressed        ");
            LATBbits.LATB8 = 1;
            Delay_ms(2000);
            LATBbits.LATB8 = 0;
            Delay_ms(2000);
            break;
        case 0b100:   //PB3 pressed
            Disp2String("\r PB3 is pressed        ");
            LATBbits.LATB8 = 1;
            Delay_ms(3000);
            LATBbits.LATB8 = 0;
            Delay_ms(3000);
            break;
        case 0b101:   //PB1 & PB3 pressed
            Disp2String("\r PB1 and PB3 are pressed");
            LATBbits.LATB8 = 1;
            break;
        case 0b110:   //PB2 & PB3 pressed
            Disp2String("\r PB2 and PB3 are pressed");
            LATBbits.LATB8 = 1;
            break;
        case 0b011:   //PB1 & PB2 pressed
            Disp2String("\r PB1 and PB2 are pressed");
            LATBbits.LATB8 = 1;
            break;
        case 0b111:   //All PBs pressed
            Disp2String("\r All PBs pressed        ");
            LATBbits.LATB8 = 1;
            break;
        default:   //no pushbuttons
            Disp2String("\r Nothing pressed        ");
            LATBbits.LATB8 = 0;
            NewClk(32); //Slow down clock once interrupt subroutine is finished 
            Delay_ms(10);
            break;
    }
}



