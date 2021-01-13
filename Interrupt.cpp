#include "Def.h"
#include "Interrupt.h"
#include "Init.h"
#include "Timer.h"


//*********************************************************************************
//*********************************************************************************
void SetTimeIntervalBuf(long *aryInfo, long *aryTimeBuf)
{
    //////long Time_Buf = aryTimeBuf[timePassInterval];
    
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
    if(100 >= interval_time)
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
    if(500 < interval_time)
        aryIntervalCount[enmOver501]++;
}


//*********************************************************************************
void Int_DetIn_PE()
{
    OrderAir(AryInfoPE, AryTimeBuf_PE);
}

//*********************************************************************************
void Int_DetIn_W()
{
    OrderAir(AryInfoW, AryTimeBuf_W);
}

//*********************************************************************************
void OrderAir(long *aryInfo, long *aryTimeBuf)
{
    //初回はスルーチェック無し
    if(aryTimeBuf[timeGetDetect]  != 0 && 
        !CheckElapsedTime(aryTimeBuf[timeGetDetect], TIME_CANCEL_NEXT_DETECT)) return;

    if(aryInfo[areaState] == enm_Sts0_WaitDetection)
    {
        // //aryInfo[areaState] = enm_Sts1_Wait;
        aryInfo[areaState] = enm_Sts1_CheckPassOn;
        GetTime(aryTimeBuf[timeWaitStart]);
        GetTime(aryTimeBuf[timeGetDetect]);
    }
}
