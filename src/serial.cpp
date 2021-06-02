#include <Arduino.h>
#include "serial.h"
#include "modes.h"
#include "timer.h"

byte received;

//todo - commands to set / get oscillate speed

void setupSerial()
{
    Serial.begin(115200);
    Serial.println("Serial Started.");
}

void sendStatus()
{
    Serial.print(powerOn() ? "P" : "p");
    Serial.print(fluctuateOn() ? "F" : "f");
    Serial.print(fluctuateWithPowerOn() ? "}" : "{");
    Serial.print(oscillateOn() ? "O" : "o");
    Serial.print(oscillateWithPowerOn() ? ")" : "(");

    switch (speedLevel())
    {
    case 1:
        Serial.print("l");
        break;
    case 2:
        Serial.print("m");
        break;
    case 3:
        Serial.print("h");
        break;
    }

    switch (speedWithPowerOn())
    {
    case 1:
        Serial.print("L");
        break;
    case 2:
        Serial.print("M");
        break;
    case 3:
        Serial.print("H");
        break;
    }

    Serial.println(hoursRemaining(), HEX);
}

void processSerial()
{
    if (Serial.available())
    {
        received = Serial.read();

        switch (received)
        {
        case 'x':
            setTimer(1);
            break;
        case '?':
            sendStatus();
            break;
        case 'P':
            setPower(true);
            break;
        case 'p':
            setPower(false);
            break;
        case 'O':
            setOscillate(true);
            break;
        case 'o':
            setOscillate(false);
            break;
        case '{':
            setFluctuateWithPowerOn(false);
            break;
        case '}':
            setFluctuateWithPowerOn(true);
            break;
        case 'F':
            setFluctuate(true);
            break;
        case 'f':
            setFluctuate(false);
            break;
        case '(':
            setOscillateWithPowerOn(false);
            break;
        case ')':
            setOscillateWithPowerOn(true);
            break;

        //Speeds
        case 'l':
            setSpeed(FAN_SPEED_LOW);
            break;
        case 'm':
            setSpeed(FAN_SPEED_MED);
            break;
        case 'h':
            setSpeed(FAN_SPEED_HIGH);
            break;
        case 'L':
            setSpeedWithPowerOn(FAN_SPEED_LOW);
            break;
        case 'M':
            setSpeedWithPowerOn(FAN_SPEED_MED);
            break;
        case 'H':
            setSpeedWithPowerOn(FAN_SPEED_HIGH);
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if (!powerOn())
                setPower(true);
            setTimer((received - 48) * 60); //48 being '0' 's ascii code
            break;
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
            if (!powerOn())
                setPower(true);
            setTimer(((received - 97) + 10) * 60); //97 being 'a' 's ascii code, 10 because 'a' - 97 would be 0
            break;
        }
    }
}
