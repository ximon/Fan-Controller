#include "timer.h"
#include <Arduino.h>

uint32_t timerLastCheckTime = 0;
int timerRemainingMinutes = TIMER_DISABLED;

void updateTimer()
{
    uint32_t elapsed = millis() - timerLastCheckTime;

    if (elapsed / 60000)
    {
#ifdef debug
        Serial.println("One minute has passed, decrementing timer");
#endif
        timerRemainingMinutes -= 1;
        timerLastCheckTime = millis();
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

    if (timerRemainingMinutes > 0)
        timerLastCheckTime = millis();

#ifdef debug
    Serial.println(timerRemainingMinutes);
#endif
}

void changeTimer()
{
#ifdef debug
    Serial.print("changeTimer()-> mins = ");
#endif

    int remainingHours = (timerRemainingMinutes / 60);

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