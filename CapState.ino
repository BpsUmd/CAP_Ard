/*
 Name:    CAP_Ctrl.ino
 Created: 2020/12/15 15:35:40
 Author:  BPS-Umeda
*/

#include "Def.h"
#include "Init.h"
#include "Timer.h"
#include "Interrupt.h"

//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
void setup() {
    Serial.begin(115200);
    InitPort();//ポートのイニシャライズ
#ifdef DEBUG_TIME_SEND
    digitalWrite(PORT_LED, LED_ON);
    digitalWrite(PORT_LED_PE, LED_ON);
    digitalWrite(PORT_LED_W, LED_ON);
    digitalWrite(PORT_LED_AIR, LED_ON);
    delay(1000);
    digitalWrite(PORT_LED, LED_OFF);
    digitalWrite(PORT_LED_PE, LED_OFF);
    digitalWrite(PORT_LED_W, LED_OFF);
    digitalWrite(PORT_LED_AIR, LED_OFF);
#else //DEBUG_TIME_SEND
    FlashLED(PORT_LED, 3, 50, LED_OFF);
    FlashLED(PORT_LED_PE, 3, 50, LED_OFF);
    FlashLED(PORT_LED_W, 3, 50, LED_OFF);
    FlashLED(PORT_LED_AIR, 3, 50, LED_OFF);
#endif //DEBUG_TIME_SEND

    //割り込み設定
    attachInterrupt(INT_NUM_AREA2, Int_SetPassOnTimePE, FALLING);
    attachInterrupt(INT_NUM_AREA2, Int_DetectionPE, RISING);

    attachInterrupt(INT_NUM_AREA3, Int_SetPassOnTimeW, FALLING);
    attachInterrupt(INT_NUM_AREA3, Int_DetectionW, RISING);

    Serial.println("-----Start-----");
}

//*********************************************************************************
void loop() 
{
    //CtrlSignal(AryInfoPE, FlgPE, AREA_NUM_PE);
    //CtrlSignal(AryInfoW, FlgW, AREA_NUM_W);
    CtrlSignal(AryInfoPE);
    CtrlSignal(AryInfoW);
}
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************

//void CtrlSignal(long *aryInfo, bool& flg, int areaNum)
void CtrlSignal(long *aryInfo)
{
    long TimeBuf = 0;
    String strAreaName = "";
    
    switch(aryInfo[areaState])
    {
        //=============================
        //通常状態
        case enm_StsWaitDetection:
            //検知信号を受けたら "通過完了割込み待ち" へ
            if(digitalRead(aryInfo[portNumDetection]) == LOW)
                ChangeState(aryInfo, enm_StsWaitPassOff);
            break;

        //=============================
        //検知を受けた後の待ち時間(通過センサより先に反応したときの為に)
        //※■※PassOFFを割り込み反応にした為、必要なくなった
        case enm_StsWaitAddition:
            // if(CheckCnt(aryInfo[cntBuf], CNT_WAIT))
            //     ChangeState(aryInfo, enm_StsWaitPassOff);
            ChangeState(aryInfo, enm_StsWaitDetection);
            break;

        //=============================
        //"通過完了割込み待ち"　割込みが来たら "エア命令発信遅延" へ
        //※■※指定時間経っても割込が無い時は通常状態に戻す
        case enm_StsWaitPassOff:
            //一定時間、割込みが無い場合は通常状態へ
            if(CheckCnt(aryInfo[cntBuf], CNT_FLG_CANCEL))
                ChangeState(aryInfo, enm_StsWaitDetection);
            break;

        //=============================
        //エア命令発信遅延
        case enm_StsWaitAirOrder:
            if(3 == 0)
                ChangeState(aryInfo, enm_StsAirSignal);
            else
            {
                //初回は時間をセット
                if(aryInfo[flgAirOrderWait] == 0)
                {
                    //wait開始時間をセット
                    GetTime(aryInfo[timeWaitStart]);
                    //待ち時間をセット
                    aryInfo[timeTargetBuf] = aryInfo[timePassSpeed] / TIME_DEVIDE;
                    aryInfo[flgAirOrderWait] = 1;
                }
                else
                {
                    if(CheckElapsedTime(aryInfo[timeWaitStart], aryInfo[timePassSpeed]))
                    {
                        aryInfo[flgAirOrderWait] = 0;
                        ChangeState(aryInfo, enm_StsAirSignal);
                        digitalWrite(aryInfo[portNumAir], HIGH);
                    }
                }
            }
            break;

        //=============================
        //エア命令ON時間
        case enm_StsAirSignal:
            if(CheckCnt(aryInfo[cntBuf], CNT_AIR_SIGNAL))
            {
                ChangeState(aryInfo, enm_StsWaitDetection);
                digitalWrite(aryInfo[portNumAir], LOW);
            }
            break;

        //=============================
        default:
            ChangeState(aryInfo, enm_StsWaitDetection);
            break;
    }
}



//*********************************************************************************
void ChangeState(long *aryInfo, int stateNum)
{
    aryInfo[areaState] = stateNum;
    
    aryInfo[cntBuf] = 0;
}

//*********************************************************************************
bool CheckCnt(long& cnt, long endNum)
{
    if(cnt >= endNum)
        return true;
    else
    {
        cnt++;
        return false;
    }
}

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
