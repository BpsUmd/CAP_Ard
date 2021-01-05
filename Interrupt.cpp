#include "Def.h"
#include "Interrupt.h"
#include "Init.h"
#include "Timer.h"

//*********************************************************************************
//エリア2 CAP通過時の割込み
//*********************************************************************************
void Int_DetectionPE()
{
    //通過時間を取得
    AryInfoPE[timePassSpeed] = TimeElapsed(AryInfoPE[timePassOn]);
    OrderAir(AryInfoPE);
}

//*********************************************************************************
//エリア3 CAP通過時の割込み
//*********************************************************************************
void Int_DetectionW()
{
    //通過時間を取得
    AryInfoW[timePassSpeed] = TimeElapsed(AryInfoW[timePassOn]);
    OrderAir(AryInfoW);
}

//*********************************************************************************
//*********************************************************************************
void OrderAir(long *aryInfo)
{
    //検知信号が無い場合は”通常状態”へ
    if(AryInfoW[areaState] != enm_StsWaitPassOff)
        ChangeState(aryInfo, enm_StsWaitDetection)
    //検知信号を受けている場合は”エア命令発信待ち”へ
    else
    {
        aryInfo[areaState] = enm_StsWaitAirOrder;
        aryInfo[cntBuf] = 0;
    }
    
    
}

//*********************************************************************************
//*********************************************************************************
void Int_SetPassOnTimePE()
{
    GetTime(AryInfoPE[timePassOn]);
}

//*********************************************************************************
//*********************************************************************************
void Int_SetPassOnTimeW()
{
    GetTime(AryInfoW[timePassOn]);
}