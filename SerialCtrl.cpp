#include <Arduino.h>
#include "SerialCtrl.h"

//*********************************************************************************
void SendSerial(HardwareSerial serialA, String strMessage, bool blLn)
{
    if(blLn)
        serialA.println(strMessage);
    else
        serialA.print(strMessage);
}

//*********************************************************************************
bool ReceiveSerial(HardwareSerial& serialA)
{
    char charBuf;
    while(serialA.available() > 0)
    {
        charBuf = serialA.read();
        if(charBuf == 0x0d || charBuf == 0x0a) return true;
    }

    return false;
}
