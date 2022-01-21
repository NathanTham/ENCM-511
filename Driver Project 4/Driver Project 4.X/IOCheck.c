/*
 * File:   IOCheck.c
 * Author: Nathan
 *
 * Created on November 13, 2021, 4:47 PM
 */

#include "xc.h"

int PBstate = 0b000;
extern int PB1; //PB1 from gpio.c
extern int PB2; //PB2 from gpio.c
extern int PB3; //PB3 from gpio.c
uint16_t ADCvalue; 

void IOCheck()
{
    //PB1 : RA2
    //PB2 : RA4
    //PB3 : RB4
    
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
            //ADCvalue = ADC(); 
            //Disp2String("/n%d",ADCvalue);
            break;
        case 0b010:   //PB2 pressed
            Disp2String("\r PB2 is pressed        ");
            break;
        case 0b100:   //PB3 pressed
            Disp2String("\r PB3 is pressed        ");
            break;
        case 0b101:   //PB1 & PB3 pressed
            Disp2String("\r PB1 and PB3 are pressed");
            break;
        case 0b110:   //PB2 & PB3 pressed
            Disp2String("\r PB2 and PB3 are pressed");
            break;
        case 0b011:   //PB1 & PB2 pressed
            Disp2String("\r PB1 and PB2 are pressed");
            break;
        case 0b111:   //All PBs pressed
            Disp2String("\r All PBs pressed        ");
            break;
        default:   //no pushbuttons
            Disp2String("\r Nothing pressed        ");
            Delay_ms(10);
            break;
    }
}