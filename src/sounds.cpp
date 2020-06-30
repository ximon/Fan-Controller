#include <Arduino.h>
#include "pitches.h"
#include "pins.h"
#include "sounds.h"

bool powerOnTone = false;

void setupBuzzer()
{
    pinMode(Buzzer_Low, OUTPUT);
    digitalWrite(Buzzer_Low, HIGH);
}

void playMarioCoinSound()
{
    //Mario coin sound
    tone(Buzzer_Low, NOTE_B5, 100);
    delay(100);
    tone(Buzzer_Low, NOTE_E6, 850);
    delay(800);
    noTone(Buzzer_Low);
}

void playMario1UpSound()
{
    //Mario 1-up sound
    tone(Buzzer_Low, NOTE_E6, 125);
    delay(130);
    tone(Buzzer_Low, NOTE_G6, 125);
    delay(130);
    tone(Buzzer_Low, NOTE_E7, 125);
    delay(130);
    tone(Buzzer_Low, NOTE_C7, 125);
    delay(130);
    tone(Buzzer_Low, NOTE_D7, 125);
    delay(130);
    tone(Buzzer_Low, NOTE_G7, 125);
    delay(125);
    noTone(Buzzer_Low);
}

void playOnTone()
{
    if (powerOnTone)
        playMarioCoinSound();
}

void playButtonTone()
{
    playMarioCoinSound();
}

void playKonamiTone()
{
    playMario1UpSound();
}