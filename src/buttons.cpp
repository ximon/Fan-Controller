#include "buttons.h"
#include <Arduino.h>
#include "pins.h"
#include "modes.h"
#include "timer.h"

#define debug

bool buttonTone = false;

bool powerPressed;
bool fluctuatePressed;
bool oscillatePressed;
bool speedPressed;
bool timerPressed;
unsigned int lastButtonPressTime;

void checkPowerButton() { 
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

}

void checkFluctuateButton(){ 
        if (!digitalRead(Fluctuate_Button))
    {
        if (!fluctuatePressed)
        {
            lastButtonPressTime = millis();
            fluctuatePressed = true;

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
}

void checkOscillateButton(){
    if (!digitalRead(Oscillate_Button))
    {
        if (!oscillatePressed)
        {
            lastButtonPressTime = millis();
            oscillatePressed = true;

#ifdef debug
            Serial.println("Oscillate Pressed");
#endif
           
            setOscillate(!oscillateOn());
            
        }
        //todo - advance oscillate speed when button held
    }
    else
    {
        oscillatePressed = false;
    }
}

void checkSpeedButton() {
    if (!digitalRead(Speed_Button))
    {
        if (!speedPressed)
        {
            lastButtonPressTime = millis();
            speedPressed = true;

#ifdef debug
            Serial.println("Speed Pressed");
#endif

            changeSpeed();
        }
    }
    else
    {
        speedPressed = false;
    }
}
void checkTimerButton() { 
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
            return;
        }
        
        if (millis() - 1000 > lastButtonPressTime && lastButtonPressTime > 0)
        {
            //button is held for 1s+
            setTimer(TIMER_DISABLED);
        }
    }
    else
    {
        timerPressed = false;
    }
}

void checkButtons()
{
    checkPowerButton();
    checkFluctuateButton();
    checkOscillateButton();
    checkSpeedButton();
    checkTimerButton();
}
