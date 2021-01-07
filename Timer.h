#include <Arduino.h>

long TimeElapsed(long start_time);
long GetTime(long *valTime);
bool CheckElapsedTime(long startTime, long targetTime);
void SettingTime(long *ary_time_buf, long set_wait_time);