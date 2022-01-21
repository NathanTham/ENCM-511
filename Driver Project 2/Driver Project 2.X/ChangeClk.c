/*
 * File:   ChangeClk.c
 * Author: Nathan
 *
 * Created on October 16, 2021, 2:38 PM
 */


#include "xc.h"
#include "ChangeClk.h"

void ChangeClk(unsigned int clkval) {
    char COSCNOSC;
    if (clkval == 8) //8MHz 
        COSCNOSC == 0x00; 
    else if (clkval == 500) //500kHz 
        COSCNOSC == 0x66; 
    else if (clkval == 32) //32kHz
        COSCNOSC == 0x55;
    else //defaults 31kHz
        COSCNOSC = 0x55; 
 
    SRbits.IPL = 7;  //Disable interrupts
     CLKDIVbits.RCDIV = 0;  // CLK division = 0
     __builtin_write_OSCCONH(COSCNOSC);   // (0x00) for 8MHz; (0x66) for 500kHz; (0x55) for 32kHz;
     __builtin_write_OSCCONL(0x01);
     OSCCONbits.OSWEN=1;
     while(OSCCONbits.OSWEN==1)
     {} 
     SRbits.IPL = 0;  //enable interrupts
}
