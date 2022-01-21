/*
 * File:   ADC.c
 * Author: Nathan
 *
 * Created on November 13, 2021, 4:58 PM
 */


#include "xc.h"

uint16_t ADC(int mode) 
{
    uint16_t ADCvalue;          //16 bit register used to hold ADC converted digital output ADC1BUF0
    
    //ADC Initialization 
    AD1CON1bits.ADON = 0b1;         //turn on ADC module
    AD1CON1bits.FORM = 0b00;        //set digital output as integer
    AD1CON1bits.SSRC = 0b111;       //internal counter ends sampling and starts conversion (auto-convert) )
    AD1CON1bits.ASAM = 0b0;         //sampling begins when user sets SAMP bit 

    AD1CON2bits.VCFG = 0b000;       //Use PIC supply voltage as reference voltage
    AD1CON2bits.CSCNA = 0b0;        //Only using one input
    AD1CON2bits.SMPI = 0b0000;      //Interrupts at the completion of conversion for each sample/convert sequence
    AD1CON2bits.BUFM = 0b0;         //Buffer configured as one 16-word buffer
    AD1CON2bits.ALTS = 0b0;         //Use MUX A input multiplexer settings
    
    AD1CON3bits.ADRC = 0b0;         //Clock derived from system clock 
    AD1CON3bits.SAMC = 0b11111;     //Auto-sample time bits     Slowest sampling time = 31*2/fclk   CHOOSE THIS VALUE
    AD1CON3bits.ADCS = 0b11111;     //A->D conversion clock select bits     CHOOSE THIS VALUE
    
    AD1CHSbits.CH0NA = 0b0;         //Set negative reference voltage as Vr-
    
    // Select which analog input is given to the ADC
    if (mode == 0b0001)
        AD1CHSbits.CH0SA = 0b0101;      //Set positive analog input as AN5 (Voltmeter)
    else if (mode == 0b0010)
        AD1CHSbits.CH0SA = 0b1011;      //Set positive analog input as AN12 (Ohmmeter)
    else if (mode == 0b0100)
        AD1CHSbits.CH0SA = 0b0011;      //Set positive analog input as AN3 (Capacitor-meter)
    else if (mode == 0b1000)
        AD1CHSbits.CH0SA = 0b1010;      //Set positive analog input as AN10 (Frequency-meter)
    else
        AD1CHSbits.CH0SA = 0b0101;      //Set positive analog input as AN5 (Voltmeter)
    //AD1PCFG = 0x0000;
    //AD1CSSL = 0x0000;
    
    //ADC Sampling and Conversion 
    AD1CON1bits.SAMP = 0b1;        //Start sampling, conversion start automatically after (SSRC & SAMC settings)
    while(AD1CON1bits.DONE == 0)
    {
    }
    
    ADCvalue = ADC1BUF0;
    AD1CON1bits.SAMP = 0b0;       //Stop sampling
    AD1CON1bits.ADON = 0b0;       //Turn off ADC, ADC value stored in ADC1BUF0
    return(ADCvalue);
}

void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void)
{
    IFS0bits.AD1IF = 0;
}