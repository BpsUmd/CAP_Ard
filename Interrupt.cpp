#include "Interrupt.h"
#include "Init.h"
#include "Def.h"

//*********************************************************************************
void IntDetectionPE()
{
    if(AryStsPE[areaState] != enm_StsWaitPassOff) return;
    OrderAir(AryStsPE);
}

//*********************************************************************************
void IntDetectionW()
{
    if(AryStsW[areaState] != enm_StsWaitPassOff) return;
    OrderAir(AryStsW);
}

//*********************************************************************************
void OrderAir(long *arySts)
{
    digitalWrite(arySts[portNumAir], HIGH);
    arySts[areaState] = enm_StsAirSignal;
    arySts[cntBuf] = 0;
}