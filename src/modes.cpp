#include <Arduino.h>
#include "modes.h"
#include "timer.h"
#include "pins.h"

int fluctuateTimeMin = 1000;
int fluctuateTimeMax = 8000;

int fluctuateSpeedMin = SPEED_LOW;
int fluctuateSpeedMax = SPEED_HIGH;

int speed = SPEED_OFF;  //fan speed
bool oscillate = false; //fan oscillation
bool fluctuate = false; //fluctuate speeds
int speedBeforeFluctuate = SPEED_LOW;
int fluctuateSpeed = SPEED_LOW;
uint32_t nextFluctuateSpeedChange = 0;

bool oscillateWithPowerOn = false;
bool fluctuateWithPowerOn = false;
int speedWithPowerOn = SPEED_LOW;

void setupOutputs()
{
    //INPUT so that the pins are Hi-Z
    pinMode(Oscillate_Pin, INPUT);
    pinMode(HighSpeed_Pin, INPUT);
    pinMode(MediumSpeed_Pin, INPUT);
    pinMode(LowSpeed_Pin, INPUT);
}

void updateFluctuateSpeed()
{
    if (nextFluctuateSpeedChange < millis())
    {
        fluctuateSpeed = random(fluctuateSpeedMin, fluctuateSpeedMax + 1);
        nextFluctuateSpeedChange = millis() + random(fluctuateTimeMin, fluctuateTimeMax + 1);
    }
}

void updateOutputs()
{
    if (fluctuateOn())
    {
        updateFluctuateSpeed();
        speed = fluctuateSpeed;
    }

    int speedLevel = speed;

    pinMode(Oscillate_Pin, oscillateOn() ? OUTPUT : INPUT);
    pinMode(HighSpeed_Pin, speedHigh() ? OUTPUT : INPUT);
    pinMode(MediumSpeed_Pin, speedMed() ? OUTPUT : INPUT);
    pinMode(LowSpeed_Pin, speedLow() ? OUTPUT : INPUT);

    if (oscillateOn())
        digitalWrite(Oscillate_Pin, LOW);

    if (speedLevel == SPEED_LOW)
        digitalWrite(HighSpeed_Pin, LOW);

    if (speedLevel == SPEED_MED)
        digitalWrite(MediumSpeed_Pin, LOW);

    if (speedLevel == SPEED_HIGH)
        digitalWrite(LowSpeed_Pin, LOW);
}

int speedLevel() { return speed; }
bool speedLow() { return speed == SPEED_LOW; }
bool speedMed() { return speed == SPEED_MED; }
bool speedHigh() { return speed == SPEED_HIGH; }
bool powerOn() { return speed != SPEED_OFF; }
bool oscillateOn() { return oscillate; }
bool fluctuateOn() { return fluctuate; }

void setFluctuateWithPowerOn(bool value)
{
    fluctuateWithPowerOn = value;
}

void setFluctuate(bool value)
{
#ifdef debug
    Serial.print("Changing Fluctuate from ");
    Serial.print(fluctuate ? "on" : "off");
    Serial.print(" to ");
#endif

    fluctuate = value;

    //set the fluctuate level to match the current level until it gets changed
    if (fluctuateOn())
    {
        speedBeforeFluctuate = speedLevel();
        fluctuateSpeed = speedLevel();
    }
    else
    {
        setSpeed(speedBeforeFluctuate);
    }

#ifdef debug
    Serial.println(fluctuate ? "on" : "off");
#endif
}

void setOscillateWithPowerOn(bool value)
{
    oscillateWithPowerOn = value;
}

void setOscillate(bool value)
{
#ifdef debug
    Serial.print("Changing Oscillate from ");
    Serial.print(oscillate ? "on" : "off");
    Serial.print(" to ");
#endif

    oscillate = value;

#ifdef debug
    Serial.println(oscillate ? "on" : "off");
#endif
}

void setSpeedWithPowerOn(int speedLevel)
{
    speedWithPowerOn = speedLevel;
}

void setSpeed(int speedLevel)
{
#ifdef debug
    Serial.print("Changing Speed from ");
    Serial.print(speed);
    Serial.print(" to ");
#endif

    if (speedLevel > SPEED_HIGH)
        speedLevel = SPEED_HIGH;

    if (speedLevel < SPEED_OFF)
        speedLevel = SPEED_OFF;

    speed = speedLevel;

#ifdef debug
    Serial.println(speed);
#endif
}

void changeSpeed()
{
    setSpeed(speed == SPEED_HIGH
                 ? SPEED_LOW
                 : speed + 1);
}

void setPower(bool value)
{
    //if we're already in the deisred state then dont change anything
    if (powerOn() == value)
        return;

    if (value)
    {
#ifdef debug
        Serial.println("Turning on");
#endif
        setSpeed(speedWithPowerOn);
        setOscillate(oscillateWithPowerOn);
        setFluctuate(fluctuateWithPowerOn);
    }
    else
    {
#ifdef debug
        Serial.println("Turning off");
#endif
        setFluctuate(false);
        setOscillate(false);
        setTimer(TIMER_DISABLED);
        setSpeed(SPEED_OFF);
    }
}