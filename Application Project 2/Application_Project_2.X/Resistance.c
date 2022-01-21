/*
 * File:   Resistance.c
 * Author: Dan Tran
 *
 * Created on December 2, 2021, 2:37 PM
 */


#include "xc.h"

void ResistanceCheck(void)
{
//    Disp2String("\n\rResistanceCheck() Hit");
    uint16_t ADCvalue = ADC(0b0010);                    //voltage from ADC
    float voltage = ADCvalue*0.00313;                   //voltage=ADCBUF*Vres
    float resistance = 1000*(1/((3.25/voltage)-1));     //voltage divider to find resistance of second resistor in series
    DisplayOhms(resistance);
    Delay_ms(1000);
}
