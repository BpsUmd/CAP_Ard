#include "Init.h"

bool FlgPE = false;
bool FlgW = false;
int DebugCntAAA = 0;

long AryInfoPE[16] = {0,
                     PORT_SENSOR_PASS_2,
                     PORT_DETECTION_PE,
                     PORT_AIR_PE,
                     0,0,0,0,0,0,0,0,0,0,0,0};

long AryInfoW[16] = {0,
                    PORT_SENSOR_PASS_3,
                    PORT_DETECTION_W,
                    PORT_AIR_W,
                    0,0,0,0,0,0,0,0,0,0,0,0};

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
    digitalWrite(PORT_LED, LED_OFF);
    digitalWrite(PORT_LED_PE, LED_OFF);
    digitalWrite(PORT_LED_W, LED_OFF);
    digitalWrite(PORT_LED_AIR, LED_OFF);
}