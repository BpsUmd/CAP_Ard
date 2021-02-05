#include "Init.h"

bool FlgPE = false;
bool FlgW = false;
int DebugCntAAA = 0;

long AryInfoPE[7] = {0,
                     PORT_SENSOR_PASS_2,
                     PORT_DETECTION_PE,
                     PORT_AIR_PE,
                     PORT_LED_PE,
                     0,1};

long AryInfoW[7] = {0,
                    PORT_SENSOR_PASS_3,
                    PORT_DETECTION_W,
                    PORT_AIR_W,
                    PORT_LED_W,
                    0,1};

long AryTimeBuf_PE[10] = {0,0,0,0,0,0,0,0,0,0};
long AryTimeBuf_W[10] = {0,0,0,0,0,0,0,0,0,0};

long AryIntervalCount_PE[11] = {0,0,0,0,0,0,0,0,0,0,0};
long AryIntervalCount_W[11] = {0,0,0,0,0,0,0,0,0,0,0};

//*********************************************************************************
void InitPort()
{
    //----------------------------
    pinMode(PORT_DEBUG_PE, OUTPUT);
    pinMode(PORT_DEBUG_W, OUTPUT);
    digitalWrite(PORT_DEBUG_PE, LOW);
    digitalWrite(PORT_DEBUG_W, LOW);
    //----------------------------

    //ポート設定----------------------
    pinMode(PORT_DETECTION_PE, INPUT_PULLUP);
    pinMode(PORT_DETECTION_W, INPUT_PULLUP);

    pinMode(PORT_SENSOR_PASS_2, INPUT_PULLUP);
    pinMode(PORT_SENSOR_PASS_3, INPUT_PULLUP);

    pinMode(PORT_AIR_PE, OUTPUT);
    pinMode(PORT_AIR_W, OUTPUT);

    pinMode(PORT_LED, OUTPUT);
    pinMode(PORT_LED_PE, OUTPUT);
    pinMode(PORT_LED_W, OUTPUT);
    pinMode(PORT_LED_AIR, OUTPUT);
    
    //ポート状態------------------------
    digitalWrite(PORT_AIR_PE, AIR_OFF);
    digitalWrite(PORT_AIR_W, AIR_OFF);
    
    digitalWrite(PORT_LED, HIGH);
    digitalWrite(PORT_LED_PE, LED_OFF);
    digitalWrite(PORT_LED_W, LED_OFF);
    digitalWrite(PORT_LED_AIR, LED_OFF);
}