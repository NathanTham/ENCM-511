/*
 * File:   Display.c
 * Author: dgtra
 *
 * Created on December 2, 2021, 4:27 PM
 */


#include "xc.h"

void DisplayVoltage(float voltage)
{
    char value[5];
    sprintf(value, "%1.4f", voltage);
    Disp2String("     \r");
    Disp2String("VOLTMETER Voltage = ");
    Disp2String(value);
    Disp2String(" V");
    Disp2String("              \r");
    Delay_ms(500);
}

void DisplayOhms(float resistance)
{    
    char value[7];
    sprintf(value, "%1.4f", resistance);
    Disp2String("     \r");
    Disp2String("OHMMETER Resistance = ");
    Disp2String(value);
    Disp2String(" Ohms");
    Delay_ms(500);
}

void DisplayCapacitance(double capacitance)
{
    char value[5];
    sprintf(value, "%1.4f", capacitance);
    Disp2String("     \r");
    Disp2String("Capacitance = ");
    Disp2String(value);
    Disp2String(" uF");
    Disp2String("              \r");
    Delay_ms(500);
}

void DisplayFrequency(double frequency)
{
    char value[5];
    sprintf(value, "%1.4f", frequency);
    Disp2String("     \r");
    Disp2String("Frequency = ");
    Disp2String(value);
    Disp2String(" Hz");
    Disp2String("              \r");
    Delay_ms(500);
}

void DisplayNoFrequency()
{
    Disp2String("\rNo Frequency Detected        ");
    Delay_ms(500);
}