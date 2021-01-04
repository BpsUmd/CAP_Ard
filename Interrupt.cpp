#include "Interrupt.h"
#include "Init.h"
#include "Def.h"

//*********************************************************************************
void IntDetectionPE()
{
    if(AryStsPE[areaState] != STATE_WAIT_PASS_OFF) return;
    OrderAir(AryStsPE);
}

//*********************************************************************************
void IntDetectionW()
{
    if(AryStsW[areaState] != STATE_WAIT_PASS_OFF) return;
    OrderAir(AryStsW);
}

//*********************************************************************************
void OrderAir(long *arySts)
{
    digitalWrite(arySts[portNumAir], HIGH);
    arySts[areaState] = STATE_AIR_SIGNAL;
    arySts[cntBuf] = 0;
}