/*
 * File:   mainredo.c
 * Author: Nathan
 *
 * Created on September 29, 2021, 5:47 PM
 */


#include "xc.h"

int main(void) {
    //Outputs
    TRISBbits.TRISB7 = 0;
    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB9 = 0; 
    TRISAbits.TRISA6 = 0;
    TRISBbits.TRISB12 = 0; 
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB14 = 0; 
    TRISBbits.TRISB15 = 0; 
    TRISAbits.TRISA5 = 0;  
    
    //Inputs
    TRISBbits.TRISB1 = 1; 
    TRISBbits.TRISB2 = 1; 
    TRISBbits.TRISB4 = 1; 
    TRISAbits.TRISA4 = 1;
    
    int UCID[] = {3, 0, 0, 4, 6, 1, 1, 9}; 
    int input;
    
    while (1)
    {
        input = 0x00;
        int output[9] = {0,0,0,0,0,0,0,0,0};
        int counter;
        
        if(PORTBbits.RB1 == 1)
            input += 0x01; 
        if(PORTBbits.RB2 == 1)
            input += 0x02;
        if(PORTBbits.RB4 == 1)
            input += 0x04;
        if(PORTAbits.RA4 == 1)
            input += 0x07;
        
        if (input > 0 && input < 9)
        {
            for(counter = 0; counter < UCID[input-1]; counter++)
            {
                output[counter]= 1;
            }
        }
        
        LATBbits.LATB7 = output[0]; 
        LATBbits.LATB8 = output[1]; 
        LATBbits.LATB9 = output[2]; 
        LATAbits.LATA6 = output[3]; 
        LATBbits.LATB12 = output[4]; 
        LATBbits.LATB13 = output[5];
        LATBbits.LATB14 = output[6]; 
        LATBbits.LATB15 = output[7];
        LATAbits.LATA5 = output[8];
        
    }
    
    return 0;
}
