#include <Arduino.h>
#include "Def.h"

extern bool FlgPE;
extern bool FlgW;
extern int DebugCntAAA;

//=============================
extern long AryInfoPE[6];
extern long AryInfoW[6];

enum _EnmAryInfo
{
    areaState = 0,
    portNumPass,
    portNumDetection,
    portNumAir,
    portNumLED,
    // //cntBuf,
    // //flgAirOrderWaitStart,//Air命令waitを開始しているか
    flgPassFirstTime
};

//=============================
extern long AryTimeBuf_PE[10];
extern long AryTimeBuf_W[10];

enum _TimeBuf
{
    timeWaitStart = 0,
    timeTargetBuf,
    timePassOn,
    timePassEnd,
    timeWaitPassStart,
    timeGetDetect,
    timePassSpeed,
    timePassSpeedMin,
    timePassInterval,
    timePassIntervalMin
    // // timeAirSignalEnd,
    // // timeAirInterval,
    // // timeAirIntervalMin,
    // // timeAirIntervalAvr
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
    enm_Sts0_WaitDetection = 0,
    // // enm_Sts1_Wait,
    enm_Sts1_CheckPassOn,
    enm_Sts2_WaitPassOff,
    enm_Sts3_AirSignal
};


void InitPort();