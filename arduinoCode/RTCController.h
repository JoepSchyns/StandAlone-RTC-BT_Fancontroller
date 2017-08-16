

#ifndef RTCController_h
#define RTCController_h

#include "Arduino.h"
#include <Time.h>

//rtc libaries
#include <RTClib.h>
#include <Wire.h>

#include <StringSplitter.h>

class RTCController {
  private:
    static RTC_DS3231 rtc;
    static uint32_t syncProvider();
    
  public:
    RTCController();
    String timeString();
    void adjustRTC(StringSplitter *command);
    void printTime();
    String static time_tReadable(time_t t);
};

#endif
