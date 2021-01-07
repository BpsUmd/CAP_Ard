#include "Timer.h"
#include "Init.h"
#include "Def.h"

//*********************************************************************************
long GetTime(long *valTime)
{
    valTime = millis();
}

//*********************************************************************************
long TimeElapsed(long startTime)
{
    long resultTime = 0;
    long nowTime = millis();

    //millilの値がリセットされたときの対処
    if(nowTime < startTime)
        resultTime = nowTime + (TIME_MAX_VALUE - startTime);
    else
        resultTime = nowTime - startTime;

    return resultTime;
}

//*********************************************************************************
bool CheckElapsedTime(long start_time, long wait_time)
{
    long nowTime = millis();
    long resultTime;

    if(start_time > nowTime)
        resultTime = nowTime + (TIME_MAX_VALUE - start_time);
    else
        resultTime = nowTime - start_time;
    
    if(resultTime >= wait_time)
        return true;
    else
        return false;
}


