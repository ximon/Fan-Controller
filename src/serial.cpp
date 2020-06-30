#include <Arduino.h>
#include "serial.h"
#include "modes.h"
#include "timer.h"

byte received;

void setupSerial()
{
    Serial.begin(115200);
}

void sendStatus()
{
    Serial.print(powerOn() ? "P" : "p");
    Serial.print(fluctuateOn() ? "F" : "f");
    Serial.print(oscillateOn() ? "O" : "o");

    switch (speedLevel())
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
        case '[':
            setFluctuateWithPowerOn(false);
            break;
        case ']':
            setFluctuateWithPowerOn(true);
            break;
        case 'F':
            setFluctuate(true);
            break;
        case 'f':
            setFluctuate(false);
            break;
        case '{':
            setOscillateWithPowerOn(false);
            break;
        case '}':
            setOscillateWithPowerOn(true);
            break;

        //Speeds
        case 'l':
            setSpeed(SPEED_LOW);
            break;
        case 'm':
            setSpeed(SPEED_MED);
            break;
        case 'h':
            setSpeed(SPEED_HIGH);
            break;
        case 'L':
            setSpeedWithPowerOn(SPEED_LOW);
            break;
        case 'M':
            setSpeedWithPowerOn(SPEED_MED);
            break;
        case 'H':
            setSpeedWithPowerOn(SPEED_HIGH);
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
