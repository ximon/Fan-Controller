#include <Arduino.h>
#include "display.h"
#include "modes.h"
#include "pins.h"
#include "timer.h"

int displayGroup = DISPLAY_GROUP_1;
bool flashing = false;
unsigned long lastFlashTime = 0;

void setupDisplay()
{
    //INPUT PULLUP so that the buttons can be read
    pinMode(Group1Low, INPUT_PULLUP);
    pinMode(Group2Low, INPUT_PULLUP);
    pinMode(Group3Low, INPUT_PULLUP);

    pinMode(Group1Hi, INPUT_PULLUP);
    pinMode(Group2Hi, INPUT_PULLUP);
    pinMode(Group3Hi, INPUT_PULLUP);
}

void setNextDisplayMode()
{
    displayGroup = displayGroup == DISPLAY_GROUP_3
                       ? DISPLAY_GROUP_1
                       : displayGroup + 1;
}

void disableDisplay()
{
    //Low Drives
    pinMode(Group1Low, INPUT_PULLUP);
    pinMode(Group2Low, INPUT_PULLUP);
    pinMode(Group3Low, INPUT_PULLUP);

    //High Drives
    pinMode(Group1Hi, INPUT_PULLUP);
    pinMode(Group2Hi, INPUT_PULLUP);
    pinMode(Group3Hi, INPUT_PULLUP);
}

void updateDisplay()
{
    //if the fan isn't on then dont turn the display on at all
    if (!powerOn())
        return;

    pinMode(Group1Low, OUTPUT);
    pinMode(Group2Low, OUTPUT);
    pinMode(Group3Low, OUTPUT);

    pinMode(Group1Hi, OUTPUT);
    pinMode(Group2Hi, OUTPUT);
    pinMode(Group3Hi, OUTPUT);

    int hours = hoursRemaining();

    if (hours % 2 != 0)
    {
        if (millis() - 500 > lastFlashTime)
        {
            flashing = !flashing;
            lastFlashTime = millis();
        }
    }
    else
    {
        flashing = false;
    }

    bool LED8 = false;
    bool LED4 = false;
    bool LED2 = false;

    if (!flashing && hours > 0)
    {
        LED8 = ((hours + 1) & 0x08) > 0;
        LED4 = ((hours + 1) & 0x04) > 0;
        LED2 = ((hours + 1) & 0x02) > 0;
    }

    bool group1H = false;
    bool group2H = false;
    bool group3H = false;

    switch (displayGroup)
    {
    case DISPLAY_GROUP_1:
        group1H = fluctuateOn();
        group2H = speedLow();
        group3H = powerOn();
        break;
    case DISPLAY_GROUP_2:
        group1H = LED8;
        group2H = LED2;
        group3H = oscillateOn();
        break;
    case DISPLAY_GROUP_3:
        group1H = LED4;
        group2H = speedMed();
        group3H = speedHigh();
        break;
    }

    digitalWrite(Group1Low, !(displayGroup == DISPLAY_GROUP_1));
    digitalWrite(Group2Low, !(displayGroup == DISPLAY_GROUP_2));
    digitalWrite(Group3Low, !(displayGroup == DISPLAY_GROUP_3));

    digitalWrite(Group1Hi, group1H);
    digitalWrite(Group2Hi, group2H);
    digitalWrite(Group3Hi, group3H);
}