#include <Arduino.h>
#include "pins.h"
#include "modes.h"
#include "timer.h"
#include "display.h"
#include "sounds.h"
#include "buttons.h"
#include "ir.h"
#include "serial.h"

//todo - poweron settings in eeprom
const int LOOP_TIME = 5; //ms

uint32_t lastLoopTime;

void timerElapsed()
{
  disableDisplay();

  setNextDisplayMode();
  checkButtons();
  updateTimer();
  updateOutputs();

  updateDisplay();
}

#ifndef UNIT_TEST
void setup()
{
  setupSerial();
  setupDisplay();
  setupOutputs();
  setupIR();
  setupBuzzer();

  playOnTone();
}

void loop()
{
  if (millis() - lastLoopTime > LOOP_TIME)
  {
    lastLoopTime = millis();
    timerElapsed();
  }

  processIR();
  processSerial();
}
#endif