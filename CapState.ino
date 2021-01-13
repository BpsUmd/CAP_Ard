/*
 Name:    CAP_Ctrl.ino
 Created: 2020/12/15 15:35:40
 Author:  BPS-Umeda
*/

#include "Def.h"
#include "Init.h"
#include "Timer.h"
#include "Interrupt.h"
#include "SerialCtrl.h"

//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
//セッティング
//*********************************************************************************
//*********************************************************************************
void setup() {
    Serial.begin(115200);
    InitPort();//ポートのイニシャライズ

    //割り込み設定
    attachInterrupt(INT_NUM_AREA2, Int_DetIn_PE, FALLING);
    // attachInterrupt(INT_NUM_AREA2, Int_SetPassOnTimePE, FALLING);

    attachInterrupt(INT_NUM_AREA3, Int_DetIn_W, FALLING);
    // attachInterrupt(INT_NUM_AREA3, Int_SetPassOnTimePE, FALLING);

    FlashLED_All(100, 5);
    Serial.println("-----Start-----");

// #ifdef DEBUG_SERIAL_OUT
//     Serial.println("-----PE State 0 Wait detection-----");
//     Serial.println("-----W State 0 Wait detection-----");
// #endif
}

//*********************************************************************************
//*********************************************************************************
//メインループ
//*********************************************************************************
//*********************************************************************************
void loop() 
{
    //CtrlSignal(AryInfoPE, FlgPE, AREA_NUM_PE);
    //CtrlSignal(AryInfoW, FlgW, AREA_NUM_W);
    CtrlSignal(AryInfoPE, AryTimeBuf_PE);
    CtrlSignal(AryInfoW, AryTimeBuf_W);
    //Output_Interval_Count();
}
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************



//*********************************************************************************
//状態遷移
//*********************************************************************************
// //void CtrlSignal(long *aryInfo, bool& flg, int areaNum)
void CtrlSignal(long *aryInfo, long *aryTimeBuf)
{
    long TimeBuf = 0;

    switch(aryInfo[areaState])
    {
        //=======================================================================================
        //0 通常状態
        case enm_Sts0_WaitDetection:
#pragma region 通常状態---------------------------

            break;
#pragma endregion

        //=======================================================================================
        //待ち時間　通過より検知が先になった時の対策
        //※変更　　時間管理 → 通過ON信号を待つ
        // // case enm_Sts1_Wait:
        // //     if(CheckElapsedTime(aryTimeBuf[timeWaitStart], TIME_WAIT))
        // //     {
        // //         GetTime(aryTimeBuf[timeWaitPassStart]);
        // //         ChangeState(aryInfo, enm_Sts2_WaitPassOff);
        // //     }
        // //     break;

        //=======================================================================================
        //通過センサがオンになるまで待つ
        case enm_Sts1_CheckPassOn:
            if(digitalRead(aryInfo[portNumPass]) == PASS_ON)
                ChangeState(aryInfo, enm_Sts2_WaitPassOff);
            //いつまでもONにならない場合は検知キャンセル
            else if(CheckElapsedTime(aryTimeBuf[timeGetDetect], TIME_CANCEL))
            {
                ChangeState(aryInfo, enm_Sts0_WaitDetection);
                //LED消灯
                digitalWrite(aryInfo[portNumLED], LED_OFF);
            }
            break;


        //=======================================================================================
        //1 "通過完了待ち"　通過センサがOFFになったら、 "エア命令発信遅延" へ
        //※■※指定時間経っても割込が無い時は通常状態に戻す
        case enm_Sts2_WaitPassOff:
#pragma region 通過完了待ち---------------------------
            if(digitalRead(aryInfo[portNumPass]) == PASS_OFF)
            {
                digitalWrite(aryInfo[portNumAir], AIR_ON);
                //LED消灯
                digitalWrite(aryInfo[portNumLED], LED_OFF);
                GetTime(aryTimeBuf[timePassEnd]);
                ChangeState(aryInfo, enm_Sts3_AirSignal);
            }
            //一定時間、センサがOFFしない場合は通常状態へ
            else if(CheckElapsedTime(aryTimeBuf[timeWaitPassStart], TIME_CANCEL) && 
                        aryInfo[areaState] == enm_Sts2_WaitPassOff)
            {
                //LED消灯
                digitalWrite(aryInfo[portNumLED], LED_OFF);
                ChangeState(aryInfo, enm_Sts0_WaitDetection);
            }
            break;
#pragma endregion


        //=======================================================================================
        //エア命令ON時間
        case enm_Sts3_AirSignal:
#pragma region エア命令信号発信-------------------------------
            // if(CheckCnt(aryInfo[cntBuf], CNT_AIR_SIGNAL) && aryInfo[areaState] == enm_Sts3_AirSignal)
            if(CheckElapsedTime(aryTimeBuf[timePassEnd], TIME_AIR_SIGNAL_ON))
            {
                digitalWrite(aryInfo[portNumAir], AIR_OFF);
                ChangeState(aryInfo, enm_Sts0_WaitDetection);
            }
            break;
#pragma endregion

    }
}


//*********************************************************************************
//状態変更
//*********************************************************************************
void ChangeState(long *aryInfo, int stateNum)
{
    aryInfo[areaState] = stateNum;
    // // aryInfo[cntBuf] = 0;
}

//*********************************************************************************
//カウントとカウント数チェック
//*********************************************************************************
// // bool CheckCnt(long& cnt, long endNum)
// // {
// //     if(cnt >= endNum)
// //         return true;
// //     //カウンタをインクリメント
// //     else
// //     {
// //         cnt++;
// //         return false;
// //     }
// // }

//*********************************************************************************
//指定LED点灯
//*********************************************************************************
void FlashLED(int portNum, int loopNum, int delayTime, bool blEnd)
{
    for (int i = 0; i < loopNum; i++)
    {
        digitalWrite(portNum, LED_ON);
        delay(delayTime/20);
        digitalWrite(portNum, LED_OFF);
        delay(delayTime*10);
    }
    digitalWrite(portNum, blEnd);
}

//*********************************************************************************
//すべてのLED点灯
//*********************************************************************************
void FlashLED_All(int delayTime, int loopNum)
{
    for (int i = 0; i < loopNum; i++)
    {
        digitalWrite(PORT_LED_0, LED_ON);
        digitalWrite(PORT_LED_PE, LED_OFF);
        digitalWrite(PORT_LED_W, LED_OFF);
        delay(delayTime);
        digitalWrite(PORT_LED_0, LED_OFF);
        digitalWrite(PORT_LED_PE, LED_ON);
        digitalWrite(PORT_LED_W, LED_OFF);
        delay(delayTime);
        digitalWrite(PORT_LED_0, LED_OFF);
        digitalWrite(PORT_LED_PE, LED_OFF);
        digitalWrite(PORT_LED_W, LED_ON);
        delay(delayTime);
        digitalWrite(PORT_LED_0, LED_OFF);
        digitalWrite(PORT_LED_PE, LED_ON);
        digitalWrite(PORT_LED_W, LED_OFF);
    }
    
    for (int i = 0; i < loopNum; i++)
    {
        digitalWrite(PORT_LED_0, LED_ON);
        digitalWrite(PORT_LED_PE, LED_ON);
        digitalWrite(PORT_LED_W, LED_ON);
        delay(delayTime / 2);    
        digitalWrite(PORT_LED_0, LED_OFF);
        digitalWrite(PORT_LED_PE, LED_OFF);
        digitalWrite(PORT_LED_W, LED_OFF);    
    }
}

//*********************************************************************************
//通過スピードカウンタをシリアル送信
//*********************************************************************************
// // void Output_Interval_Count()
// // {
// //     if(ReceiveSerial(Serial))
// //     {
// //         Serial.println("=====PE=====");
// //         Serial.print("Under100ms,");
// //         Serial.println(AryIntervalCount_PE[enmUnder100]);
// //         Serial.print("101-150ms,");
// //         Serial.println(AryIntervalCount_PE[enm101_150]);
// //         Serial.print("151-200ms,");
// //         Serial.println(AryIntervalCount_PE[enm151_200]);
// //         Serial.print("201-250ms,");
// //         Serial.println(AryIntervalCount_PE[enm201_250]);
// //         Serial.print("251-300ms,");
// //         Serial.println(AryIntervalCount_PE[enm251_300]);
// //         Serial.print("301-350ms,");
// //         Serial.println(AryIntervalCount_PE[enm301_350]);
// //         Serial.print("351-400ms,");
// //         Serial.println(AryIntervalCount_PE[enm351_400]);
// //         Serial.print("401-450ms,");
// //         Serial.println(AryIntervalCount_PE[enm401_450]);
// //         Serial.print("451-500ms,");
// //         Serial.println(AryIntervalCount_PE[enm451_500]);
// //         Serial.print("Over501ms,");
// //         Serial.println(AryIntervalCount_PE[enmOver501]);
// //         Serial.println("");
// //         Serial.println("=====White=====");
// //         Serial.print("Under100ms,");
// //         Serial.println(AryIntervalCount_W[enmUnder100]);
// //         Serial.print("101-150ms,");
// //         Serial.println(AryIntervalCount_W[enm101_150]);
// //         Serial.print("151-200ms,");
// //         Serial.println(AryIntervalCount_W[enm151_200]);
// //         Serial.print("201-250ms,");
// //         Serial.println(AryIntervalCount_W[enm201_250]);
// //         Serial.print("251-300ms,");
// //         Serial.println(AryIntervalCount_W[enm251_300]);
// //         Serial.print("301-350ms,");
// //         Serial.println(AryIntervalCount_W[enm301_350]);
// //         Serial.print("351-400ms,");
// //         Serial.println(AryIntervalCount_W[enm351_400]);
// //         Serial.print("401-450ms,");
// //         Serial.println(AryIntervalCount_W[enm401_450]);
// //         Serial.print("451-500ms,");
// //         Serial.println(AryIntervalCount_W[enm451_500]);
// //         Serial.print("Over501ms,");
// //         Serial.println(AryIntervalCount_W[enmOver501]);

// //     }
// // }