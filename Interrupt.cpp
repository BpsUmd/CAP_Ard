#include "Def.h"
#include "Interrupt.h"
#include "Init.h"
#include "Timer.h"


//*********************************************************************************
//エリア2 通過開始割込み
//*********************************************************************************
void Int_SetPassOnTimePE()
{
    SetTimeIntervalBuf(AryInfoPE, AryTimeBuf_PE);
    // GetTime(AryTimeBuf_PE[timePassOn]);
}

//*********************************************************************************
//エリア3 通過開始割込み
//*********************************************************************************
void Int_SetPassOnTimeW()
{
    SetTimeIntervalBuf(AryInfoW, AryTimeBuf_W);
    // GetTime(AryTimeBuf_W[timePassOn]);
}

//*********************************************************************************
//*********************************************************************************
void SetTimeIntervalBuf(long *aryInfo, long *aryTimeBuf)
{
    long Time_Buf = aryTimeBuf[timePassInterval];
    
    //前回のON時間から通過間隔をセット
    aryTimeBuf[timePassInterval] = TimeElapsed(aryTimeBuf[timePassOn]);
    //現在時間をON時間に格納
    GetTime(aryTimeBuf[timePassOn]);

    //通過間隔の最小値をセット
    if(aryInfo[flgPassFirstTime] >= 1 || aryTimeBuf[timePassIntervalMin] > aryTimeBuf[timePassInterval])
        aryTimeBuf[timePassIntervalMin] = aryTimeBuf[timePassInterval];
}

//*********************************************************************************
void IntervalCount(long *aryIntervalCount, long interval_time)
{
    if(100 <= interval_time)
        aryIntervalCount[enmUnder100]++;
    if(100 < interval_time && 150 >= interval_time)
        aryIntervalCount[enm101_150]++;
    if(150 < interval_time && 200 >= interval_time)
        aryIntervalCount[enm151_200]++;
    if(200 < interval_time && 250 >= interval_time)
        aryIntervalCount[enm201_250]++;
    if(250 < interval_time && 300 >= interval_time)
        aryIntervalCount[enm251_300]++;
    if(300 < interval_time && 350 >= interval_time)
        aryIntervalCount[enm301_350]++;
    if(350 < interval_time && 400 >= interval_time)
        aryIntervalCount[enm351_400]++;
    if(400 < interval_time && 450 >= interval_time)
        aryIntervalCount[enm401_450]++;
    if(450 < interval_time && 500 >= interval_time)
        aryIntervalCount[enm451_500]++;
    if(500 > interval_time)
        aryIntervalCount[enmOver501]++;
}

//=======================================================================================
//=======================================================================================
//*********************************************************************************
//エリア2 CAP通過終了時の割込み
//*********************************************************************************
void Int_DetectionPE()
{
    OrderAir(AryInfoPE, AryTimeBuf_PE, AryIntervalCount_PE);
}

//*********************************************************************************
//エリア3 CAP通過終了時の割込み
//*********************************************************************************
void Int_DetectionW()
{
    //通過時間を取得
    // AryTimeBuf_W[timePassSpeed] = TimeElapsed(AryTimeBuf_W[timePassOn]);
    OrderAir(AryInfoW, AryTimeBuf_W, AryIntervalCount_W);
}

//*********************************************************************************
//*********************************************************************************
void OrderAir(long *aryInfo, long *aryTimeBuf, long *aryIntervalCount)
{
    //==============時間処理==============
    //通過時間を取得
    aryTimeBuf[timePassSpeed] = TimeElapsed(aryTimeBuf[timePassOn]);

    //==============信号処理==============
    //検知信号が無い場合は”通常状態”へ
    if(AryInfoW[areaState] != enm_StsWaitPassOff)
        AryInfoW[areaState] = enm_StsWaitDetection;
    //検知信号を受けている場合は”エア命令発信待ち”へ
    else
        aryInfo[areaState] = enm_StsWaitAirOrder;
    
    //インターバル時間をカウント
    IntervalCount(aryIntervalCount, aryTimeBuf[timePassInterval]);
    //カウンタをリセット
    aryInfo[cntBuf] = 0;
    //初回フラグをリセット
    if(AryInfoW[flgPassFirstTime] < 1)
        AryInfoW[flgPassFirstTime] = 0;
        
    //キャップ間隔情報を出力するフラグをセット
    aryInfo[flgSerialOut] = 1;
}