#include <Arduino.h>
#include "Def.h"

extern bool FlgPE;
extern bool FlgW;
extern int DebugCntAAA;

extern long AryInfoPE[16];
extern long AryInfoW[16];

enum _EnmAryInfo
{
    areaState = 0,
    portNumPass,
    portNumDetection,
    portNumAir,
    cntBuf,
    flgAirOrderWait,//0 or 1
    timeWaitStart,
    timeTargetBuf,
    timePassOn,
    timePassSpeed,
    timePassSpeedMin,
    timePassSpeedAvr,
    timeAirSignalEnd,
    timeAirInterval,
    timeAirIntervalMin,
    timeAirIntervalAvr
};

enum _StateTransition
{
    enm_StsWaitDetection = 0,
    enm_StsWaitAddition,
    enm_StsWaitPassOff,
    enm_StsWaitAirOrder,
    enm_StsAirSignal
};

void InitPort();