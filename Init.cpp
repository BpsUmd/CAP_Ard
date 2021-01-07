#include "Init.h"


long AryInfoPE[3] = {0,
                     PORT_SENSOR_PASS_2,
                     PORT_DETECTION_PE};
long AryInfoW[3] = {0,
                    PORT_SENSOR_PASS_3,
                    PORT_DETECTION_W};

long AryTimeBuf_PE[2] = {0,PASS1_DETECT1_TIME};
long AryTimeBuf_W[2] = {0,PASS1_DETECT1_TIME};

void InitPort()
{
    //ポート設定----------------------
    pinMode(PORT_DETECTION_PE, OUTPUT);
    pinMode(PORT_DETECTION_W, OUTPUT);

    pinMode(PORT_SENSOR_PASS_2, OUTPUT);
    pinMode(PORT_SENSOR_PASS_3, OUTPUT);

    pinMode(PORT_LED, OUTPUT);
    
    //ポート状態------------------------
    digitalWrite(PORT_DETECTION_PE, SIGNAL_OFF);
    digitalWrite(PORT_DETECTION_W, SIGNAL_OFF);

    digitalWrite(PORT_SENSOR_PASS_2, SIGNAL_OFF);
    digitalWrite(PORT_SENSOR_PASS_3, SIGNAL_OFF);

    digitalWrite(PORT_LED, LED_OFF);
}