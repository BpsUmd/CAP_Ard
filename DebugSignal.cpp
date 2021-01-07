#include "DebugSignal.h"
#include "Def.h"
#include "Init.h"
#include <Arduino.h>

void DebAirSignal_LED(long aryInfo)
{
    bool blOn = digitalRead(aryInfo[portNumAir]);
    //int ledSts = blOn;
#ifdef DEBUG_SIGNAL
    if(blOn)
    {
        digitalWrite(PORT_LED, LED_ON);
        if(aryInfo[portNumAir] == PORT_AIR_PE)
            digitalWrite(PORT_LED_PE, LED_ON);
        if(aryInfo[portNumAir] == PORT_AIR_W)
            digitalWrite(PORT_LED_W, LED_ON);
    }
    else
    {
        digitalWrite(PORT_LED, LED_OFF);
        if(aryInfo[portNumAir] == PORT_AIR_PE)
            digitalWrite(PORT_LED_PE, LED_OFF);
        if(aryInfo[portNumAir] == PORT_AIR_W)
            digitalWrite(PORT_LED_W, LED_OFF);
    }
#endif
}
