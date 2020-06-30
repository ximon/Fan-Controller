#ifndef __DISPLAY_H__
#define __DISPLAY_H__

const int DISPLAY_GROUP_1 = 1; //Fluctuate 8H 4H
const int DISPLAY_GROUP_2 = 2; //Low 2H Medium
const int DISPLAY_GROUP_3 = 3; //Power Oscillate High

void setupDisplay();
void setNextDisplayMode();
void disableDisplay();
void updateDisplay();

#endif