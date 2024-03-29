#include <IRremote.h> //changed boarddefs.h, changed timer 2 to timer 1
#include "ir.h"
#include "modes.h"
#include "buttons.h"
#include "timer.h"

const int IR_REPEAT_TIME = 500;

uint32_t lastIRTime;
uint32_t lastIRCmd;
unsigned long irCmd;
bool irCmdRepeated = false;

IRrecv irrecv(IR_In);

void setupIR()
{
    irrecv.enableIRIn();
}

void processIR()
{
    decode_results results; // Somewhere to store the results

    if (irrecv.decode(&results))
    {
        if (results.decode_type == NEC)
        {
            irCmd = results.value;

            if (irCmd == IR_Repeat && millis() - IR_REPEAT_TIME > lastIRTime)
            {
#ifdef debug
                Serial.print("Repeating ");
                Serial.println(lastIRCmd, HEX);
#endif
                irCmd = lastIRCmd;
                irCmdRepeated = true;
            }
            else
            {
                irCmdRepeated = false;
            }

            switch (irCmd)
            {
            case IR_Fluctuate: //fluctuate
                setFluctuate(!fluctuateOn());
                break;
            case IR_Speed: //speed
                changeSpeed();
                break;
            case IR_Power: //power
                setPower(!powerOn());
                break;
            case IR_Timer: //timer
                if (irCmdRepeated)
                {
                    setTimer(TIMER_DISABLED);
                    break;
                }

                changeTimer();
                break;
            case IR_Oscillate: //oscillate
                setOscillate(!oscillateOn());
                //todo - advance oscillate speed if button held
                break;
            }

            if (irCmd != IR_Repeat)
            {
#ifdef debug
                Serial.print("IR: 0x");
                Serial.println(irCmd, HEX);
#endif
                lastIRTime = millis();
                lastIRCmd = irCmd;
            }
        }

        irrecv.resume(); // Prepare for the next value
    }
}