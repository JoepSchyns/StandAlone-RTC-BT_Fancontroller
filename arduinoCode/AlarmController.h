#ifndef AlarmController_h
#define AlarmController_h

#include "Arduino.h"

#include <StringSplitter.h>
#include "FansController.h"
#include "RTCController.h"


//memory write library
#include <EEPROM.h>
const int memAdress = 0;

//timer libaries
#include <Time.h>
#include <TimeAlarms.h> //https://github.com/PaulStoffregen/TimeAlarms


class AlarmController {
  private:
    
    const String ON_COMMAND = "on";
    const String OFF_COMMAND = "off";
    boolean saveAlarms();
    String onOrOff(boolean on);
    boolean onOrOff(String on);
    int setAlarm(int Hour, int Minute, int Second, boolean on);
    int setAlarm(int Day, int Hour, int Minute, int Second, boolean on);
    int setTimer(int Hour, int Minute, int Second, boolean on);
    typedef void (*On_t)();
    typedef void (*Off_t)();

  public:
    AlarmController();
    int setAlarm(StringSplitter *command);
    int setTimer(StringSplitter *command);
    void removeAlarms();
    void removeAlarm(int ID);
    String alarmInfo(int ID);
    void delay(int time);
    int static count();
    
    FansController fansController;
    
};

#endif
