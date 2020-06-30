#ifndef __IR_H__
#define __IR_H__

#include "pins.h"

#define IR_Fluctuate 0xFFE01F
#define IR_Speed 0xFFF00F
#define IR_Power 0xFFC837
#define IR_Timer 0xFFC03F
#define IR_Oscillate 0xFFD02F
#define IR_Repeat 0xFFFFFFFF

void setupIR();
void processIR();

#endif