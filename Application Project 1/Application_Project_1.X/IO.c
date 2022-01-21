/*
 * File:   IO.c
 * Author: Nathan
 *
 * Created on October 23, 2021, 5:53 PM
 */

#include "xc.h"
#include "timers.h"
#include "gpio.h"

int PBstate = 0b000;
int Mode = 1; //default mode - countdown
int min = 0; //minutes
int sec = 0; //seconds
int hsec = 0; //hundreth of a second
int pressedTime = 0; //how long button has been pressed in seconds
int countStop = 0; //countdown stop flag
int timerStop = 0; //timer stop flag
int gameStop = 0; //reaction game stop flag
int alarm = 0; //alarm flag
char str[30];
extern int PB1; //PB1 from gpio.c
extern int PB2; //PB2 from gpio.c
extern int PB3; //PB3 from gpio.c

void IOinit() {
    TRISAbits.TRISA2 = 1; // Set RA2 as input (B1)
    TRISAbits.TRISA4 = 1; // Set RA4 as input (B2)
    TRISBbits.TRISB4 = 1; // Set RB4 as input (B3)
    TRISBbits.TRISB8 = 0; // Set RB8 as output (LED)

    CNPU2bits.CN30PUE = 1; // RA2 Pull up
    CNPU1bits.CN0PUE = 1; // RA4 Pull up
    CNPU1bits.CN1PUE = 1; // RB4 Pull up

    AD1PCFG = 0xFFFF;
}

void IOCheck() {
    //PB1 : RA2
    //PB2 : RA4
    //PB3 : RB4

    //Check if any pushbuttons are pressed
    if (PB1 == 1 || PB2 == 1 || PB3 == 1) {
        NewClk(8); //Set clock to 8MHz (Speed up clock after input is registered) 
    }

    PBstate = 0b000;

    if (PB1 == 1) {
        PBstate += 0b001;
    }
    if (PB2 == 1) {
        PBstate += 0b010;
    }
    if (PB3 == 1) {
        PBstate += 0b100;
    }

    switch (PBstate) {
        case 0b001: //PB1 pressed
            switch (Mode) {
                case 1: //countdown - adjust minutes
                    if (alarm == 1) {
                        alarm = 0;
                        countStop = 0;
                    }
                    if (min < 59) {
                        min = min + 1;
                        Delay_ms(200);
                    }
                    sprintf(str, "  %02dm : %02ds         ", min, sec);
                    Disp2String(str);
                    XmitUART2('\r', 1);
                    break;
                case 2: //timer - start stop
                    Delay_ms(300);
                    if (timerStop == 0) {
                        Timer();
                    } else if (timerStop == 1) {
                        timerStop = 0;
                        sprintf(str, "  %02dm : %02d.%02ds      ", min, sec, hsec);
                        Disp2String(str);
                        XmitUART2('\r', 1);
                    }
            }
            break;
        case 0b010: //PB2 pressed
            switch (Mode) {
                case 1: //countdown - adjust seconds
                    if (alarm == 1) {
                        alarm = 0;
                        countStop = 0;
                    }
                    if (sec < 59) {
                        sec = sec + 1;
                        Delay_ms(200);
                    }
                    sprintf(str, "  %02dm : %02ds         ", min, sec);
                    Disp2String(str);
                    XmitUART2('\r', 1);
                    break;
                case 2: //timer - reset
                    timerStop = 0;
                    min = 0;
                    sec = 0;
                    hsec = 0;
                    sprintf(str, "  %02dm : %02d.%02ds      ", min, sec, hsec);
                    Disp2String(str);
                    XmitUART2('\r', 1);
            }
            break;
        case 0b100: //PB3 pressed
            switch (Mode) {
                case 1: //countdown - PB3 long or short press
                    while (PB3 == 1) {
                        sprintf(str, "  %02dm : %02ds  %ds", min, sec, pressedTime);
                        Disp2String(str);
                        XmitUART2('\r', 1);
                        pressedTime = pressedTime + 1;
                        Delay_ms(1000); 
                    }
                    if (pressedTime <= 3) //countdown - start stop
                    {
                        pressedTime = 0;
                        if (min == 0 && sec == 0) {
                            countStop = 1;
                        }
                        if (countStop == 0) {
                            Countdown();
                        } else if (countStop == 1) {
                            countStop = 0;
                            sprintf(str, "  %02dm : %02ds         ", min, sec);
                            Disp2String(str);
                            XmitUART2('\r', 1);
                        }
                    }
                    if (pressedTime > 3) //countdown - reset
                    {
                        pressedTime = 0;
                        alarm = 0;
                        countStop = 0;
                        min = 0;
                        sec = 0;
                        sprintf(str, "  %02dm : %02ds         ", min, sec);
                        Disp2String(str);
                        XmitUART2('\r', 1);
                    }
                    break;
                case 2: //timer - reaction game
                    if (gameStop == 0) {
                        ReactionGame();
                    } else if (gameStop == 1) {
                        gameStop = 0;
                        sprintf(str, "  %02dm : %02d.%02ds      ", min, sec, hsec);
                        Disp2String(str);
                        XmitUART2('\r', 1);
                    }
                    break;
            }
            break;
        case 0b011: //PB1 & PB2 pressed
            while (PB1 == 1 && PB2 == 1) {
                Disp2String("\r Switching modes");
                sprintf(str, " %ds ", pressedTime);
                Disp2String(str);
                XmitUART2('\r', 1);
                pressedTime = pressedTime + 1;
                Delay_ms(1000);
            }
            if (pressedTime > 3) //Mode switch
            {
                pressedTime = 0;
                if (Mode == 1) //countdown to timer
                {
                    if (alarm == 1) {
                        alarm = 0;
                        countStop = 0;
                    }
                    Mode = 2;
                    min = 0;
                    sec = 0;
                    hsec = 0;
                    sprintf(str, "  %02dm : %02d.%02ds      ", min, sec, hsec);
                    Disp2String(str);
                    XmitUART2('\r', 1);
                } else if (Mode == 2) //timer to countdown
                {
                    Mode = 1;
                    min = 0;
                    sec = 0;
                    sprintf(str, "  %02dm : %02ds         ", min, sec);
                    Disp2String(str);
                    XmitUART2('\r', 1);
                }
            } else if (pressedTime <= 3) { //cancel mode switch
                pressedTime = 0;
                if (Mode == 1) //countdown
                {
                    sprintf(str, "  %02dm : %02ds         ", min, sec);
                    Disp2String(str);
                    XmitUART2('\r', 1);
                } else if (Mode == 2) //timer
                {
                    sprintf(str, "  %02dm : %02d.%02ds      ", min, sec, hsec);
                    Disp2String(str);
                    XmitUART2('\r', 1);
                }
            }
            break;
        default: //no pushbuttons
            if (alarm == 1) { //LED on when ALARM
                LATBbits.LATB8 = 1;
            } else if (alarm == 0) {
                LATBbits.LATB8 = 0;
            }
            NewClk(32); //Slow down clock when stop watch is not active
            Delay_ms(100);
            break;
    }
}

void Countdown() {
    int blink = 0;

    while (countStop == 0) {
        if (sec >= 0) {
            sec = sec - 1; //countdown seconds
            if (blink == 0) { //1 sec blink rate
                blink = 1;
                LATBbits.LATB8 = 1;
                Delay_ms(1000);
            } else if (blink == 1) {
                blink = 0;
                LATBbits.LATB8 = 0;
                Delay_ms(1000);
            }
            if (sec < 0) {
                min = min - 1; //countdown minutes
                sec = 59;
            }
            if (PB3 == 1) { //countdown stop flag
                countStop = 1;
                min = min;
                sec = sec + 1;
            }
            sprintf(str, "  %02dm : %02ds         ", min, sec);
            Disp2String(str);
            if (min == 0 && sec == 0) { //ALARM
                XmitUART2('\r', 1);
                sprintf(str, "  %02dm : %02ds -- ALARM", min, sec);
                Disp2String(str);
                alarm = 1;
                countStop = 1;
                LATBbits.LATB8 = 1;
            }
            XmitUART2('\r', 1);
        }
    }
}

void Timer() {
    while (timerStop == 0) {
        LATBbits.LATB8 = 1;

        hsec = hsec + 1; //increment hsec twice to account for display delays
        Delay_ms(1);
        hsec = hsec + 1;
        Delay_ms(1);
        if (hsec == 100) {
            hsec = 0;
            sec = sec + 1; //increment seconds
            if (sec > 59) {
                sec = 0;
                min = min + 1; //increment minutes
            }
        }
        if (PB1 == 1) { //timer stop flag
            timerStop = 1;
            min = min;
            sec = sec;
            hsec = hsec;
            LATBbits.LATB8 = 0;
        }
        if (PB2 == 1) { //timer reset flag
            timerStop = 1;
            min = 0;
            sec = 0;
            hsec = 0;
        }
        sprintf(str, "  %02dm : %02d.%02ds", min, sec, hsec);
        Disp2String(str);
        XmitUART2('\r', 1);
    }
}

void ReactionGame() {
    int ReadySetGo = 0;

    while (gameStop == 0) {
        if (PB2 == 1) { //game exit flag
            gameStop = 1;
            min = 0;
            sec = 0;
            hsec = 0;
        }
        if (PB3 == 1) { //game reset flag
            ReadySetGo = 0;
            min = 0;
            sec = 0;
            hsec = 0;
            sprintf(str, "  %02dm : %02d.%02ds      ", min, sec, hsec);
            Disp2String(str);
            XmitUART2('\r', 1);
        }
        if (ReadySetGo == 0) { //wait period
            Delay_ms(1000); //1 sec blink rate
            LATBbits.LATB8 = 1;
            Delay_ms(1000);
            LATBbits.LATB8 = 0;
            Delay_ms(1000);
            LATBbits.LATB8 = 1;
            Delay_ms(1000);
            LATBbits.LATB8 = 0;
            Delay_ms(1000);
            LATBbits.LATB8 = 1;
            Delay_ms(1000);
            LATBbits.LATB8 = 0;

            ReadySetGo = 1;
        }
        while (ReadySetGo == 1) { //game start
            srand(time(0));
            int r = (rand() % 2500) + 500; //random number between 500-3000
            Delay_ms(r);
            LATBbits.LATB8 = 1;
            Timer();
            timerStop = 0;
            ReadySetGo = 2;
        }
    }
}