#include "Def.h"
#include "Interrupt.h"
#include "Init.h"
#include "Timer.h"


//*********************************************************************************
//*********************************************************************************
// void SetTimeIntervalBuf(long *aryInfo, long *aryTimeBuf)
// {
//     //////long Time_Buf = aryTimeBuf[timePassInterval];
    
//     //前回のON時間から通過間隔をセット
//     aryTimeBuf[timePassInterval] = TimeElapsed(aryTimeBuf[timePassOn]);
//     //現在時間をON時間に格納
//     GetTime(aryTimeBuf[timePassOn]);

//     //通過間隔の最小値をセット
//     if(aryInfo[flgDetectFirstTime] >= 1 || aryTimeBuf[timePassIntervalMin] > aryTimeBuf[timePassInterval])
//         aryTimeBuf[timePassIntervalMin] = aryTimeBuf[timePassInterval];
// }

//*********************************************************************************
// void IntervalCount(long *aryIntervalCount, long interval_time)
// {
//     if(100 >= interval_time)
//         aryIntervalCount[enmUnder100]++;
//     if(100 < interval_time && 150 >= interval_time)
//         aryIntervalCount[enm101_150]++;
//     if(150 < interval_time && 200 >= interval_time)
//         aryIntervalCount[enm151_200]++;
//     if(200 < interval_time && 250 >= interval_time)
//         aryIntervalCount[enm201_250]++;
//     if(250 < interval_time && 300 >= interval_time)
//         aryIntervalCount[enm251_300]++;
//     if(300 < interval_time && 350 >= interval_time)
//         aryIntervalCount[enm301_350]++;
//     if(350 < interval_time && 400 >= interval_time)
//         aryIntervalCount[enm351_400]++;
//     if(400 < interval_time && 450 >= interval_time)
//         aryIntervalCount[enm401_450]++;
//     if(450 < interval_time && 500 >= interval_time)
//         aryIntervalCount[enm451_500]++;
//     if(500 < interval_time)
//         aryIntervalCount[enmOver501]++;
// }


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
    //アイドル状態じゃ無い時は検知信号を無視()
    if (aryInfo[areaState] != enm_Sts0_WaitDetection) return;

    //■PE
    if(aryInfo[portNumPass] == PORT_SENSOR_PASS_PE)
    {
        //PE検知を受けた時、通過がOFFである場合は信号を無視　※ノイズ対策
        if(digitalRead(aryInfo[portNumPass]) == PASS_OFF) return;
        //通常PE検知時は必ず通ONである為、通過OFF待ち状態へ
        aryInfo[areaState] = enm_Sts2_WaitPassOff;
    }
    //■白
    else
        //白検知が通過ONよりも早い場合の対策
        //通過ON待ち状態へ
        aryInfo[areaState] = enm_Sts1_CheckPassOn_W;

    //if(aryTimeBuf[flgDetectFirstTime] == 1)
    //    aryTimeBuf[flgDetectFirstTime] = 0;

    //検知信号を受けて無視する時間が経過していないときは処理を中断 
    //PE側：TIME_CANCEL_NEXT_DETECT_PE
    // W側：TIME_CANCEL_NEXT_DETECT_W
    //if(!CheckElapsedTime(aryTimeBuf[timeGetDetect], aryTimeBuf[timeCancelNextDetect])) return;

    // if(aryInfo[areaState] == enm_Sts0_WaitDetection)
    // {
    //aryInfo[areaState] = enm_Sts1_Wait;
    digitalWrite(aryInfo[portNumLED], LED_ON);
    GetTime(aryTimeBuf[timeWaitStart]);
    GetTime(aryTimeBuf[timeGetDetect]);
    // }

}
