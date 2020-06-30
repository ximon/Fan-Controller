#ifndef __PINS_H__
#define __PINS_H_

#define IC18 A4 //Group3 / Oscillate Button
#define IC17 2  //!Group1
#define IC16 3  //!Group3 / Power Button
#define IC15 4  //!Group2 / Fluctuate Button
//14 - OSC2
//13 - OSC1
//12 - VCC
//11 - VCC
#define IC10 5 //!Buzzer Output
#define IC9 12 //IR Output
//IC8 - GND
#define IC7 11 //!Low Speed Output
#define IC6 8  //!Medium Speed Output
#define IC5 9  //!High Speed Output
#define IC4 10 //!Oscillate Output
//IC3 - N/C
#define IC2 7 //Group1 / Timer Button
#define IC1 6 //Group2 / Speed Button

#define LowSpeed_Pin IC7    //Active Low
#define MediumSpeed_Pin IC6 //Active Low
#define HighSpeed_Pin IC5   //Active Low
#define Oscillate_Pin IC4   //Active Low

#define Group1Low IC17
#define Group2Low IC15
#define Group3Low IC16

#define Group1Hi IC2
#define Group2Hi IC1
#define Group3Hi IC18

#define IR_In IC9
#define Buzzer_Low IC10

#define Timer_Button IC2
#define Power_Button IC16
#define Speed_Button IC1
#define Fluctuate_Button IC15
#define Oscillate_Button IC18

#endif