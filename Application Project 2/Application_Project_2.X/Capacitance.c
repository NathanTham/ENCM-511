/*
 * File:   Voltage.c
 * Author: Dan Tran
 *
 * Created on November 24, 2021, 5:00 PM
 */


#include "xc.h"

void CapacitanceCheck() {
    long usec = 0;                      
    long usecNF = 0;
    LATBbits.LATB2 = 1;                                 //set pin 6 as output to begin charging capacitor
    uint16_t ADCvalue = 0;

    while (ADCvalue < 645) {                            //capacitor charging
        usec = usec + 409.967;                          //charging counter
        usecNF = usecNF + 1;                            //charging counter for small capacitors
        ADCvalue = ADC(0b0100);                         //voltage value of charging capacitor from ADC
    }

    if (usecNF != 1) {
        double capacitance = (usec / 1000.0);           //capacitance=time/resistance
        DisplayCapacitance(capacitance);
    } else {
        double capacitance = (usecNF / 1000.0);         //capacitance=time/resistance
        DisplayCapacitance(capacitance);
    }

    LATBbits.LATB2 = 0;                                 //turn pin 6 off
    while (ADCvalue > 10) {                             //wait for capacitor to discharge
        ADCvalue = ADC(0b0100);
    }
}
