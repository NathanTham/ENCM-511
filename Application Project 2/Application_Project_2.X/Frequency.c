/*
 * File:   Frequency.c
 * Author: Dan Tran
 *
 * Created on December 2, 2021, 2:49 PM
 */


#include "xc.h"

extern int Freq; //From gpio.c
double Frequency = 0;
long usec = 0;
long counter = 0;
int clockflag = 0;
int flag = 0;

void FrequencyCheck(void) {
    flag = 0;
    
    if (Freq == 0)
    {
        counter+=1;                                 //increment counter when input wave low   
    }
    if (Freq == 1 && counter>5)                     //first frequency cycle after a period of being disconnected
    {
        NewClk(8);                                  //change clock to 8MHz
    }
    if (Freq == 1)
    {
        counter = 0;                                //reset counter when input wave high
    }
    if (counter>5)                                  //2.5 seconds of no frequency input
    {   
        DisplayNoFrequency();                       //display no frequency detected
        NewClk(32);                                 //32 kHz Clock
    }
    
    if (flag == 0 && Freq == 1 && counter<5) {      //measure time when input wave high 
        while (Freq == 1) {
            usec = usec + 100;                      //counter for frequency measure
        }
        flag = 1;
        Frequency = (2000000 / usec)*10.22;         //frequency calculation
        DisplayFrequency(Frequency);
        usec = 0;
    }
}
