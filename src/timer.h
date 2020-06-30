#ifndef __TIMER_H__
#define __TIMER_H__

#include <Arduino.h>

const int TIMER_DISABLED = 0;
const int TIMER_MINS_MIN = 1 * 60;
const int TIMER_MINS_MAX = 14 * 60;

void updateTimer();
int hoursRemaining();

void setTimer(int newTimerMinutes);
void changeTimer();

#endif