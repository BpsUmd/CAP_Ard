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
    enm_Sts0_PassH_DetectH = 0,
    enm_Sts11_PassL_DetectH,
    enm_Sts12_PassH_DetectL,
    enm_Sts2_PassL_DetectL,
    enm_Sts3_PassL_DetectH
};


void InitPort();