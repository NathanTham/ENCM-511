/*
 * File:   TimeDelay.c
 * Author: Nathan
 *
 * Created on October 12, 2021, 3:10 PM
 */


#include "xc.h" 
#include "TimeDelay.h"

void Delay_ms(uint16_t time_ms) {
    
    TMR2 = 0; //Clear timer 2
    
    //Configure T2CON register bits
    T2CONbits.T32 = 0; //Keep timer 2 as discrete 16-bit timer
    T2CONbits.TSIDL = 0; //Continue module operation in idle mode
    T2CONbits.TCS = 0; //Select internal clock (Fosc/2)
    T2CONbits.TON = 1; //Starts 16-bit timer 2
    
    T2CONbits.TCKPS1 = 1; 
    T2CONbits.TCKPS0 = 1; //Sets prescaler to 1:256
    
     // Set timer2 interrupt priority to 6
    IPC1bits.T2IP2 = 1;
    IPC1bits.T2IP1 = 1;
    IPC1bits.T2IP0 = 0;
    
    // Enable timer2 interrupt
    IEC0bits.T2IE = 1;
    
    // Clear timer2 interrupt flag
    IFS0bits.T2IF = 0;
    
    PR2 = time_ms*15;
    
    Idle(); 
    
    return;
}

//ISR
void __attribute__ ((interrupt, no_auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0; //clear timer 2 interrupt flag
    T2CONbits.TON = 0; //stop timer
}