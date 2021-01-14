#include "Timer.h"
#include "Def.h"

//*********************************************************************************
void GetTime(long& valTime)
{
    valTime = millis();
}

//*********************************************************************************
// // long TimeElapsed(long startTime)
// // {
// //     long resultTime = 0;
// //     long nowTime = millis();

// //     //millilの値がリセットされたときの対処
// //     if(nowTime < startTime)
// //         resultTime = nowTime + (TIME_MAX_VALUE - startTime);
// //     else
// //         resultTime = nowTime - startTime;

// //     return resultTime;
// // }

//*********************************************************************************
bool CheckElapsedTime(long startTime, long targetTime)
{
    long nowTime = millis();
    // long resultTime;

    if(startTime > nowTime)
    {
        //resultTime = nowTime + (TIME_MAX_VALUE - startTime);
        if((nowTime + (TIME_MAX_VALUE - startTime)) >= targetTime) return true;
    }
    else
        if(nowTime - startTime >= targetTime) return true;
        // resultTime = nowTime - startTime;
    
    
    else
        return false;
}
