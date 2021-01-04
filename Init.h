#include <Arduino.h>
#include "Def.h"

extern bool FlgPE;
extern bool FlgW;
extern int DebugCntAAA;

extern long AryStsPE[13];
extern long AryStsW[13];
enum _EnmArySts
{
    areaState = 0,
    portNumPass,
    portNumDetection,
    portNumAir,
    cntBuf,
    timePassOn,
    timePassInterval,
    timePassIntervalMin,
    timePassIntervalAvr,
    timeAirSignalEnd,
    timeAirInterval,
    timeIntervalMin,
    timeIntervalAvr
};

void InitPort();