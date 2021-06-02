#include "buttons.h"
#include <Arduino.h>
#include "pins.h"
#include "modes.h"
#include "timer.h"

bool buttonTone = false;

bool powerPressed;
bool fluctuatePressed;
bool oscillatePressed;
bool speedPressed;
bool timerPressed;
unsigned int lastButtonPressTime;


void checkButtons()
{
    if (!digitalRead(Power_Button))
    {
        if (!powerPressed)
        {
            lastButtonPressTime = millis();
            powerPressed = true;

#ifdef debug
            Serial.println("Power Pressed");
#endif

            setPower(!powerOn());
        }
    }
    else
    {
        powerPressed = false;
    }

    if (!digitalRead(Fluctuate_Button))
    {
        if (!fluctuatePressed)
        {
            lastButtonPressTime = millis();
            fluctuatePressed = true;

            if (!powerOn())
                setPower(true);

#ifdef debug
            Serial.println("Fluctuate Pressed");
#endif
            setFluctuate(!fluctuateOn());
        }
    }
    else
    {
        fluctuatePressed = false;
    }

    if (!digitalRead(Oscillate_Button))
    {
        if (!oscillatePressed)
        {
            lastButtonPressTime = millis();
            oscillatePressed = true;

#ifdef debug
            Serial.println("Oscillate Pressed");
#endif

            //this one is different, turning on turns on the oscillation, so toggling it turns it back off
            if (!powerOn())
            {
                setPower(true);
                setOscillate(true);
            }
            else
            {
                setOscillate(!oscillateOn());
            }
        }
        //todo - advance oscillate speed when button held
    }
    else
    {
        oscillatePressed = false;
    }

    if (!digitalRead(Speed_Button))
    {
        if (!speedPressed)
        {
            lastButtonPressTime = millis();
            speedPressed = true;

#ifdef debug
            Serial.println("Speed Pressed");
#endif

            if (!powerOn())
                setPower(true);
            else
                changeSpeed();
        }
    }
    else
    {
        speedPressed = false;
    }

    if (!digitalRead(Timer_Button))
    {
        if (!timerPressed)
        {
            lastButtonPressTime = millis();
            timerPressed = true;

#ifdef debug
            Serial.println("Timer Pressed");
#endif

            changeTimer();
        }
        else
        {
            if (millis() - 1000 > lastButtonPressTime && lastButtonPressTime > 0)
            {
                //button is held for 1s+
                setTimer(TIMER_DISABLED);
            }
        }
    }
    else
    {
        timerPressed = false;
    }
}
