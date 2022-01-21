/*
 * File:   main.c
 * Author: Nathan
 *
 * Created on October 11, 2021, 4:36 PM
 */

// MPLAB header libraries
#include "xc.h"
#include <p24fxxxx.h>
#include <p24F16KA101.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>

#include "IOs.h"
#include "TimeDelay.h"
#include "ChangeClk.h"

//Preprocessor directives - Configuration bits for MCU start up
#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor disabled

// MACROS for Idle, Sleep modes
#define Nop() {__asm__ volatile ("nop");}
#define ClrWdt() {__asm__ volatile ("clrwdt");}
#define Sleep() {__asm__ volatile ("pwrsav #0");}   //Sleep() - put MCU in sleep mode - CPU and some peripherals off
#define Idle() {__asm__ volatile ("pwrsav #1");}    //Idle() - put MCU in idle mode - only CPU off
#define dsen() {__asm__ volatile ("BSET DSCON, #15");} 

int main(void) {
    ChangeClk(8); // 8 for 8 MHz; 500 for 500 kHz; 32 for 32 kHz
    IOinit(); 
    Config();
    
    while (1) {
    }
    
    return 0;
}

