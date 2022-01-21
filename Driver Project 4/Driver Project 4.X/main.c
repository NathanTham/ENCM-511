/*
 * File:   main.c
 * Author: Nathan
 *
 * Created on November 13, 2021, 4:21 PM
 */

// MPLAB header libraries
#include <xc.h>
#include <p24fxxxx.h>
#include <p24F16KA101.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>

// User header files
#include "config.h"
#include "gpio.h"
#include "IOCheck.h"
#include "ADC.h"
#include "timers.h"
#include "UART2.h"
#include "ChangeClk.h"

//Preprocessor directives - Configuration bits for MCU start up
#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor disabled

/*
// MACROS for Idle, Sleep modes
#define Nop() {__asm__ volatile ("nop");}
#define ClrWdt() {__asm__ volatile ("clrwdt");}
#define Sleep() {__asm__ volatile ("pwrsav #0");}   //Sleep() - put MCU in sleep mode - CPU and some peripherals off
#define Idle() {__asm__ volatile ("pwrsav #1");}    //Idle() - put MCU in idle mode - only CPU off
#define dsen() {__asm__ volatile ("BSET DSCON, #15");} 
*/

void main(void) {
    NewClk(8);
    Config();
    
    while(1)
    {
        IOCheck();
    }
    
    return;
}
//Need to initialize pin 8 as analog potentiometer input 
