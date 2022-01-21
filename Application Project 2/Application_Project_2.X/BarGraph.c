/*
 * File:   BarGraph.c
 * Author: Dan Tran
 *
 * Created on November 24, 2021, 7:35 PM
 */


#include "xc.h"
//Used for Driver Project 4
void BarGraph(uint32_t voltage)
{
    int graph = (voltage+1)/64;
    int spaces = 16-graph;
    Disp2String("     \r");
    Disp2String("[");
    XmitUART2('!',graph);
    XmitUART2(' ',spaces);
    Disp2String("]    "); 
    
    Disp2Hex(voltage);
}
