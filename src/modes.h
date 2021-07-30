#ifndef __MODES_H__
#define __MODES_H__

const int FAN_SPEED_OFF = 0;
const int FAN_SPEED_LOW = 1;
const int FAN_SPEED_MED = 2;
const int FAN_SPEED_HIGH = 3;

const int OSCILLATE_SPEED_ON = 91;

void setupOutputs();
void updateOutputs();

int speedLevel();
bool speedLow();
bool speedMed();
bool speedHigh();
bool powerOn();

bool oscillateOn();
bool oscillateWithPowerOn();
bool fluctuateOn();
bool fluctuateWithPowerOn();

void setFluctuateWithPowerOn(bool value);
void setFluctuate(bool value);

void setOscillateWithPowerOn(bool value);
void setOscillate(bool value);

void setSpeedWithPowerOn(int speedLevel);
int speedWithPowerOn();
void setSpeed(int speedLevel);
void changeSpeed();

void setTimer(int newTimerMinutes);
void changeTimer();

void setPower(bool value);

#endif