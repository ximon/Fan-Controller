#include <Arduino.h>
#include <Servo.h>
#include "modes.h"
#include "timer.h"
#include "pins.h"

#define debug

Servo oscillateServo;

int fluctuateTimeMin = 1000;
int fluctuateTimeMax = 8000;

int fluctuateSpeedMin = FAN_SPEED_LOW;
int fluctuateSpeedMax = FAN_SPEED_HIGH;

int speed = FAN_SPEED_OFF;  //fan speed

bool oscillate = false; //fan oscillation
#define OSCILLATE_MIN_ANGLE 5
#define OSCILLATE_MAX_ANGLE 130
#define OSCILLATE_START_ANGLE OSCILLATE_MAX_ANGLE /2 + OSCILLATE_MIN_ANGLE
int oscillateUpdateDelay = OSCILLATE_SPEED_LOW; //ms
int oscillateAngle = OSCILLATE_START_ANGLE;
int oscillateDelta = 1;
unsigned long oscillateLastUpdate;

bool fluctuate = false;
int speedBeforeFluctuate = FAN_SPEED_LOW;
int fluctuateSpeed = FAN_SPEED_LOW;
unsigned long nextFluctuateSpeedChange = 0;

bool oscillateWithPower = false;
bool fluctuateWithPower = false;
int speedWithPower = FAN_SPEED_LOW;

void setupOutputs()
{
    oscillateServo.attach(Oscillate_Pin);
    oscillateServo.write(oscillateAngle);

    //INPUT so that the pins are Hi-Z
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

bool oscillateNeedsUpdate() { 
    return millis() - oscillateLastUpdate >= oscillateUpdateDelay;
}

void updateOutputs()
{
    if (fluctuateOn())
    {
        updateFluctuateSpeed();
        speed = fluctuateSpeed;
    }

    pinMode(HighSpeed_Pin, speedHigh() ? OUTPUT : INPUT);
    pinMode(MediumSpeed_Pin, speedMed() ? OUTPUT : INPUT);
    pinMode(LowSpeed_Pin, speedLow() ? OUTPUT : INPUT);

    if (oscillateOn() && oscillateNeedsUpdate())
    {
        oscillateLastUpdate = millis();

        if (oscillateAngle <= OSCILLATE_MIN_ANGLE)
            oscillateDelta = 1;

        if (oscillateAngle >= OSCILLATE_MAX_ANGLE)
            oscillateDelta = -1;

        oscillateAngle += oscillateDelta;
        oscillateServo.write(oscillateAngle);
    }

    if (speedHigh())
        digitalWrite(HighSpeed_Pin, LOW);

    if (speedMed())
        digitalWrite(MediumSpeed_Pin, LOW);

    if (speedLow())
        digitalWrite(LowSpeed_Pin, LOW);
}

int speedLevel() { return speed; }
bool speedLow() { return speed == FAN_SPEED_LOW; }
bool speedMed() { return speed == FAN_SPEED_MED; }
bool speedHigh() { return speed == FAN_SPEED_HIGH; }

bool powerOn() { return speed != FAN_SPEED_OFF; }

bool oscillateWithPowerOn() { return oscillateWithPower; }
bool oscillateOn() { return oscillate; }

bool fluctuateWithPowerOn() { return fluctuateWithPower; }
bool fluctuateOn() { return fluctuate; }

void setFluctuateWithPowerOn(bool value)
{
    fluctuateWithPower = value;
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
    oscillateWithPower = value;
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

int speedWithPowerOn()
{
    return speedWithPower;
}

void setSpeedWithPowerOn(int speedLevel)
{
    speedWithPower = speedLevel;
}

void setSpeed(int speedLevel)
{
#ifdef debug
    Serial.print("Changing Speed from ");
    Serial.print(speed);
    Serial.print(" to ");
#endif

    if (speedLevel > FAN_SPEED_HIGH)
        speedLevel = FAN_SPEED_HIGH;

    if (speedLevel < FAN_SPEED_OFF)
        speedLevel = FAN_SPEED_OFF;

    speed = speedLevel;

#ifdef debug
    Serial.println(speed);
#endif
}

void changeSpeed()
{
    setSpeed(speed == FAN_SPEED_HIGH
                 ? FAN_SPEED_LOW
                 : speed + 1);
}

void setPower(bool value)
{
    //if we're already in the desired state then dont change anything
    if (powerOn() == value)
        return;

    if (value)
    {
#ifdef debug
        Serial.println("Turning on");
#endif
        setSpeed(speedWithPower);
        setOscillate(oscillateWithPower);
        setFluctuate(fluctuateWithPower);
    }
    else
    {
#ifdef debug
        Serial.println("Turning off");
#endif
        setFluctuate(false);
        setOscillate(false);
        setTimer(TIMER_DISABLED);
        setSpeed(FAN_SPEED_OFF);
    }
}