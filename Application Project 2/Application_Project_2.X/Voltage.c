/*
 * File:   Voltage.c
 * Author: Dan Tran
 *
 * Created on November 24, 2021, 5:00 PM
 */


#include "xc.h"

void VoltageCheck()
{
    //Disp2String("\n\rVoltageCheck() Hit");
    uint16_t ADCvalue = ADC(0b0001);            //voltage value from ADC
    float voltage = ADCvalue*0.00313;           //voltage=ADCBUF*Vres
    DisplayVoltage(voltage);
    Delay_ms(1000);
}
