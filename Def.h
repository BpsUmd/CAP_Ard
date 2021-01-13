//#define DEBUG_TIME_SEND
//#define SERIAL_SEND
//#define DEBUG_SERIAL_OUT
//#define DEBUG_SIGNAL


//論理-----------------------
#define LED_ON 1
#define LED_OFF 0

#define AIR_ON 0
#define AIR_OFF 1

// #define AIR_SIGNAL_ON 1
// #define AIR_SIGNAL_OFF 0

#define PASS_ON 0
#define PASS_OFF 1

//Port番号-----------------------
#define PORT_SENSOR_PASS_2 4
#define PORT_SENSOR_PASS_3 5

#define PORT_DETECTION_PE 2//割込み
#define PORT_DETECTION_W 3//割込み

#define PORT_AIR_PE 6
#define PORT_AIR_W 7

#define PORT_LED 13
#define PORT_LED_PE 14
#define PORT_LED_W 15
#define PORT_LED_AIR 16

//割込み番号------------------------
#define INT_NUM_AREA2 0
#define INT_NUM_AREA3 1

//時間
#define TIME_WAIT 50
#define TIME_AIR_SIGNAL_ON 50
#define TIME_CANCEL 1000
#define TIME_CANCEL_NEXT_DETECT 250

//カウント閾------------------------
// #define CNT_AIR_SIGNAL 1000
#define CNT_AIR_SIGNAL 5000

#define CNT_FLG_CANCEL 62000
#define CNT_WAIT 5000

//その他-----------------------
#define AREA_NUM_PE 2
#define AREA_NUM_W 3

#define TIME_MAX_VALUE 4294967295
#define TIME_DEVIDE 0

//デバッグ用--------------------------
#define CNT_DEBUG 100000
#define PORT_DEBUG_PE 11
#define PORT_DEBUG_W 12
