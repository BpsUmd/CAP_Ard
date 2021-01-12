//#define DEBUG_TIME_SEND
//#define SERIAL_SEND
//#define DEBUG_SERIAL_OUT
//#define DEBUG_SIGNAL

//論理-----------------------
#define LED_ON 1
#define LED_OFF 0

#define SIGNAL_ON LOW
#define SIGNAL_OFF HIGH

//Port番号-----------------------
#define PORT_SENSOR_PASS_2 2//割込み
#define PORT_SENSOR_PASS_3 3//割込み

#define PORT_DETECTION_PE 4
#define PORT_DETECTION_W 5

#define PORT_LED 13

#define TIME_MAX_VALUE 4294967295

#define PASS1_DETECT1_TIME 20
#define PASS1_DETECT0_TIME 30
#define PASS0_DETECT0_TIME 20
#define PASS0_DETECT1_TIME 80
//#define PASS0_DETECT1_TIME2 100

//________            ____            __
//        |__________|    |__________|
//_____     ____________    __________
//     |___|            |__|
//     30 20  80      20

#define DELAY_PASS_W 500