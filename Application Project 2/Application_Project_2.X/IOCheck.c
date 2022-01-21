/*
 * File:   IOCheck.c
 * Author: Nathan
 *
 * Created on November 13, 2021, 4:47 PM
 */

#include "xc.h"

int PBstate = 0b000;
int MultimeterMode = 0b000;
extern int flag;
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
//        Disp2String("\n\rPB1 Pressed ");
    }
    if (PB2 == 1)
    {
        PBstate+=0b010;
//        Disp2String("\n\rPB2 Pressed ");
    }
    if (PB3 == 1)
    {
        PBstate+=0b100;
//        Disp2String("\n\rPB3 Pressed ");
    }
    
//    if (PBstate != 0b000) //no PBs pressed
//    {
//        MultimeterMode = PBstate;
//        
//    }
    
    if (PBstate == 0b001)                           //PB1 pressed
    {
        NewClk(8);                                  //Change clock to 8MHz
        VoltageCheck();
    }
    else if (PBstate == 0b010)                      //PB2 pressed
    {
        NewClk(8);                                  //Change clock to 8MHz
        ResistanceCheck();
    }
    else if (PBstate == 0b100)                      //PB3 pressed
    {
        NewClk(8);                                  //Change clock to 8MHz
        CapacitanceCheck();
    }    
    else if (PBstate == 0b011)                      //PB1 & PB2 pressed
    {
        if (REFOCONbits.RODIV == 0b1111)            //Change frequency of output wave
        { 
            REFOCONbits.ROEN = 0;
            REFOCONbits.RODIV = 0b1110;             
            REFOCONbits.ROEN = 1;
        }
        else if (REFOCONbits.RODIV == 0b1110)       //Change frequency of output wave
        {
           REFOCONbits.ROEN = 0;
           REFOCONbits.RODIV = 0b1111;
           REFOCONbits.ROEN = 1;
        }
        Delay_ms(300);
    }
    else
    {
        FrequencyCheck();
    }
    Delay_ms(500);
}