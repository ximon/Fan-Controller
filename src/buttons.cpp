#include "buttons.h"
#include <Arduino.h>
#include "pins.h"
#include "sounds.h"
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
int buttonHistory[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int konami[10] = {BTN_FLUCTUATE, BTN_FLUCTUATE, BTN_OSCILLATE, BTN_OSCILLATE, BTN_SPEED, BTN_TIMER, BTN_SPEED, BTN_TIMER, BTN_POWER, BTN_POWER};

void addButton(int button)
{
    if (buttonTone)
        playButtonTone();

    //shift buttons left one
    for (int i = 1; i < 10; i++)
    {
        buttonHistory[i - 1] = buttonHistory[i];
    }
    buttonHistory[9] = button;

#ifdef debug
    Serial.print("ButtonHistory: [");
    for (int i = 0; i < 10; i++)
    {
        Serial.print(buttonHistory[i]);
        Serial.print(", ");
    }
    Serial.println("]");
#endif
}

void checkKonami()
{
    //check for konami code
    for (int i = 0; i < 10; i++)
    {
        if (buttonHistory[i] != konami[i])
            return;
    }

    //clear buttons
    for (int i = 0; i < 10; i++)
    {
        buttonHistory[i] = 0;
    }

    playKonamiTone();
    buttonTone = !buttonTone;
}

void checkButtons()
{
    if (!digitalRead(Power_Button))
    {
        if (!powerPressed)
        {
            lastButtonPressTime = millis();
            powerPressed = true;
            addButton(BTN_POWER);

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
            addButton(BTN_FLUCTUATE);

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
            addButton(BTN_OSCILLATE);

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
            addButton(BTN_SPEED);

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
            addButton(BTN_TIMER);

            if (!powerOn())
                setPower(true);

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

    checkKonami();
}
