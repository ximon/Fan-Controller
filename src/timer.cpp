#include <Arduino.h>
#include "timer.h"
#include "modes.h"

unsigned long timerLastCheckTime = 0;
int timerRemainingMinutes = 0;
bool timerEnabled = false;

void updateTimer()
{
    if (!timerEnabled)
        return;

    unsigned long elapsed = millis() - timerLastCheckTime;

    if (elapsed / 60000)
    {
#ifdef debug
        Serial.println("One minute has passed, decrementing timer");
#endif
        timerRemainingMinutes -= 1;
        timerLastCheckTime = millis();

        if (timerRemainingMinutes == 0)
        {
            timerEnabled = false;
            setPower(false);
        }
    }
}

int hoursRemaining()
{
    if (timerRemainingMinutes == 0)
        return 0;

    return ((timerRemainingMinutes - 1) / 60) + 1;
}

void setTimer(int newTimerMinutes)
{
#ifdef debug
    Serial.print("Changing Timer from ");
    Serial.print(timerRemainingMinutes);
    Serial.print(" to ");
#endif
    if (newTimerMinutes > TIMER_MINS_MAX)
        newTimerMinutes = TIMER_MINS_MAX;

    if (newTimerMinutes < TIMER_MINS_MIN)
        newTimerMinutes = TIMER_DISABLED;

    timerRemainingMinutes = newTimerMinutes;
    timerEnabled = timerRemainingMinutes > 0;

    if (timerRemainingMinutes > 0)
    {
        timerLastCheckTime = millis();

        if (!powerOn())
            setPower(true);
    }
#ifdef debug
    Serial.println(timerRemainingMinutes);
#endif
}

void changeTimer()
{
    int remainingHours = (timerRemainingMinutes / 60);

#ifdef debug
    Serial.print("changeTimer() -> remainingHours = ");
    Serial.println(remainingHours);
    Serial.print("changeTimer()-> mins = ");
#endif

    int mins = timerRemainingMinutes == TIMER_DISABLED
                   ? 60
                   : (remainingHours * 60) + 60;
#ifdef debug
    Serial.println(mins);
#endif

    if (mins > TIMER_MINS_MAX)
        mins = TIMER_DISABLED;

#ifdef debug
    Serial.print("changeTimer()-> mins (after check) = ");
    Serial.println(mins);
#endif

    setTimer(mins);
}