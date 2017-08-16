#ifndef RTCController_h
#define RTCController_h

#include "Arduino.h"
#include <Time.h>

//rtc libaries
#include <Wire.h>
#include "RTClib.h"

#include <StringSplitter.h>

class RTCController {
  private:
    RTC_DS3231 rtc;
    uint32_t syncProvider();
    
  public:
    RTCController();
    String timeString();
    void adjustRTC(StringSplitter *command);
    void printTime();
    String static time_tReadable(time_t t);
};

#endif
