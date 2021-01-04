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
    attachInterrupt(INT_NUM_AREA2, IntDetectionPE, RISING);
    attachInterrupt(INT_NUM_AREA3, IntDetectionW, RISING);

    Serial.begin(115200);
}

//*********************************************************************************
void loop() 
{
    CtrlSignal(AryStsPE, FlgPE, AREA_NUM_PE);
    CtrlSignal(AryStsW, FlgW, AREA_NUM_W);
}
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************


//*********************************************************************************
void CtrlSignal(long *arySts, bool& flg, int areaNum)
{
    long TimeBuf = 0;
    String strAreaName = "";
    
    switch(arySts[areaState])
    {
        //STATE_WAIT_DETECTION
        //通常状態
        case 0:
            if(digitalRead(arySts[portNumDetection]) == LOW)
                ChangeState(arySts, STATE_WAIT_DETECTION);
                //arySts[areaState] = STATE_WAIT_ADDITION;
            break;
        //STATE_WAIT_ADDITION
        //検知を受けた後の待ち時間(通過センサより先に反応したときの為に)
        //※■※PassOFFを割り込み反応にした為、必要なくなった
        case 1:
            // if(CheckCnt(arySts[cntBuf], CNT_WAIT))
            //     ChangeState(arySts, STATE_WAIT_DETECTION);
            break;
        //STATE_WAIT_DETECTION
        //検知の割込待ち状態　
        //※■※指定時間経っても割込が無い時は通常状態に戻す
        case 2:
            if(CheckCnt(arySts[cntBuf], CNT_FLG_CANCEL))
                ChangeState(arySts, STATE_WAIT_DETECTION);
            break;
        //air signal on time
        //エア命令ON時間
        case 3:
            if(CheckCnt(arySts[cntBuf], CNT_AIR_SIGNAL))
            {
                ChangeState(arySts, STATE_WAIT_DETECTION);
                digitalWrite(arySts[portNumAir], LOW);
            }
            break;
    }
}



//*********************************************************************************
void ChangeState(long *arySts, int stateNum)
{
    arySts[areaState] = stateNum;
    
    arySts[cntBuf] = 0;
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
