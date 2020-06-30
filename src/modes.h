#ifndef __MODES_H__
#define __MODES_H__

const int SPEED_OFF = 0;
const int SPEED_LOW = 1;
const int SPEED_MED = 2;
const int SPEED_HIGH = 3;

void setupOutputs();
void updateOutputs();

int speedLevel();
bool speedLow();
bool speedMed();
bool speedHigh();
bool powerOn();
bool oscillateOn();
bool fluctuateOn();

void setFluctuateWithPowerOn(bool value);
void setFluctuate(bool value);

void setOscillateWithPowerOn(bool value);
void setOscillate(bool value);

void setSpeedWithPowerOn(int speedLevel);
void setSpeed(int speedLevel);
void changeSpeed();

void setTimer(int newTimerMinutes);
void changeTimer();

void setPower(bool value);

#endif