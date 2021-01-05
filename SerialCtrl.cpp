#include <Arduino.h>
#include "SerialCtrl.h"

void SendSerial(HardwareSerial serialA, String strMessage, bool blLn)
{
    if(blLn)
        serialA.println(strMessage);
    else
        serialA.print(strMessage);
}