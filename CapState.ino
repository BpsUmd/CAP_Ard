/*
 Name:    CAP_Ctrl.ino
 Created: 2020/12/15 15:35:40
 Author:  BPS-Umeda
*/

#include "Def.h"
#include "Init.h"
#include "Timer.h"
#include "SerialCtrl.h"

//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
void setup() {
    Serial.begin(115200);
    InitPort();//ポートのイニシャライズ
#ifdef DEBUG_SERIAL_OUT
    Serial.println("-----Start-----");
    Serial.println("State: 0");
#endif
}

//*********************************************************************************
void loop() 
{
    SignalCtrl(AryInfoPE, AryTimeBuf_PE);
    SignalCtrl(AryInfoW, AryTimeBuf_W);
}
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************

void SignalCtrl(long *ary_info, long *ary_time_buf)
{
    switch(ary_info[areaState])
    {
        case enm_Sts0_PassH_DetectH:
            if(CheckElapsedTime(ary_time_buf[timeStart], ary_time_buf[timeWait]))
                ChangeState(ary_info, ary_time_buf, enm_Sts11_PassL_DetectH, PASS0_DETECT1_TIME1);
            break;
        case enm_Sts11_PassL_DetectH:
            if(CheckElapsedTime(ary_time_buf[timeStart], ary_time_buf[timeWait]))
                ChangeState(ary_info, ary_time_buf, enm_Sts2_PassL_DetectL, PASS0_DETECT0_TIME);
            break;
        case enm_Sts12_PassH_DetectL:
            break;
        case enm_Sts2_PassL_DetectL:
            if(CheckElapsedTime(ary_time_buf[timeStart], ary_time_buf[timeWait]))
                ChangeState(ary_info, ary_time_buf, enm_Sts3_PassL_DetectH, PASS0_DETECT1_TIME2);
            break;
        case enm_Sts3_PassL_DetectH:
            // if(CheckElapsedTime(ary_info[timeStart], ary_time_buf[timeWait]))
            //     ChangeState(ary_info, enm_Sts0_PassH_DetectH, PASS1_DETECT1_TIME);
            if(CheckElapsedTime(ary_time_buf[timeStart], ary_time_buf[timeWait]))
            {
                ChangeState(ary_info, ary_time_buf, enm_Sts0_PassH_DetectH, PASS1_DETECT1_TIME);
                if(ary_info[portNumDetection] == PORT_DETECTION_W)
                    ary_time_buf[timeWait] += DELAY_PASS_W;
            }
            break;
    }
}

//*********************************************************************************
void ChangeState(long *ary_info, long *ary_time_buf, long target_state, long set_wait_time)
{
    switch (target_state)
    {
        case enm_Sts0_PassH_DetectH:
            ary_info[areaState] = enm_Sts0_PassH_DetectH;
            digitalWrite(ary_info[portNumPass], HIGH);
            digitalWrite(ary_info[portNumDetection], HIGH);
            digitalWrite(PORT_LED, LED_OFF);
            break;
        case enm_Sts11_PassL_DetectH:
            ary_info[areaState] = enm_Sts11_PassL_DetectH;
            digitalWrite(ary_info[portNumPass], LOW);
            digitalWrite(ary_info[portNumDetection], HIGH);
            digitalWrite(PORT_LED, LED_ON);
            break;
        case enm_Sts12_PassH_DetectL:
            ary_info[areaState] = enm_Sts12_PassH_DetectL;
            digitalWrite(ary_info[portNumPass], HIGH);
            digitalWrite(ary_info[portNumDetection], LOW);
            digitalWrite(PORT_LED, LED_OFF);
            break;
        case enm_Sts2_PassL_DetectL:
            ary_info[areaState] = enm_Sts2_PassL_DetectL;
            digitalWrite(ary_info[portNumPass], LOW);
            digitalWrite(ary_info[portNumDetection], LOW);
            digitalWrite(PORT_LED, LED_ON);
            break;
        case enm_Sts3_PassL_DetectH:
            ary_info[areaState] = enm_Sts3_PassL_DetectH;
            digitalWrite(ary_info[portNumPass], LOW);
            digitalWrite(ary_info[portNumDetection], HIGH);
            digitalWrite(PORT_LED, LED_ON);
            break;
        default:
            break;
    }
    SettingTime(ary_time_buf, set_wait_time);

#ifdef DEBUG_SERIAL_OUT
    Serial.print("State: ");
    Serial.println(target_state);
#endif

}

//***************************************************a******************************
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
