#include <Arduino.h>
#include "Def.h"

extern bool FlgPE;
extern bool FlgW;
extern int DebugCntAAA;

//=============================
extern long AryInfoPE[8];
extern long AryInfoW[8];

enum _EnmAryInfo
{
    areaState = 0,
    portNumPass,
    portNumDetection,
    portNumAir,
    cntBuf,
    flgAirOrderWait,//0 or 1
    flgSerialOut,
    flgPassFirstTime
};

//=============================
extern long AryTimeBuf_PE[7];
extern long AryTimeBuf_W[7];

enum _TimeBuf
{
    timeWaitStart = 0,
    timeTargetBuf,
    timePassOn,
    // timePassOff,
    timePassSpeed,
    timePassSpeedMin,
    timePassInterval,
    timePassIntervalMin
    // timeAirSignalEnd,
    // timeAirInterval,
    // timeAirIntervalMin,
    // timeAirIntervalAvr
};

//=============================
extern long AryIntervalCount_PE[11];
extern long AryIntervalCount_W[11];

enum _IntervalCount
{
    enmUnder100 = 0,
    enm101_150,
    enm151_200,
    enm201_250,
    enm251_300,
    enm301_350,
    enm351_400,
    enm401_450,
    enm451_500,
    enmOver501
};

//=============================
enum _StateTransition
{
    enm_StsWaitDetection = 0,
    //enm_StsWaitAddition,
    enm_StsWaitPassOff,
    enm_StsWaitAirOrder,
    enm_StsAirSignal
};


void InitPort();