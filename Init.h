#include <Arduino.h>
#include "Def.h"

//=============================
extern long AryInfoPE[3];
extern long AryInfoW[3];

enum _EnmAryInfo
{
    areaState = 0,
    portNumPass,
    portNumDetection,
};

//=============================
extern long AryTimeBuf_PE[2];
extern long AryTimeBuf_W[2];

enum _TimeBuf
{
    timeStart,
    timeWait
};

//=============================
enum _StateTransition
{
    enm_Sts0_Pass1_Detect1 = 0,
    enm_Sts1_Pass1_Detect0,
    enm_Sts2_Pass0_Detect1,
    enm_Sts3_Pass0_Detect1
};

//=============================
void InitPort();