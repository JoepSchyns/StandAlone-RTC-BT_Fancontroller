//  TimeAlarms.h - Arduino Time alarms header for use with Time library

#ifndef TimeAlarms_h
#define TimeAlarms_h

#include <Arduino.h>
#include "TimeLib.h"

#define dtNBR_ALARMS 10  // assume non-AVR has more memory


#define USE_SPECIALIST_METHODS  // define this for testing

typedef enum {
  dtMillisecond,
  dtSecond,
  dtMinute,
  dtHour,
  dtDay
} dtUnits_t;

typedef struct {
  uint8_t alarmType      :4 ;  // enumeration of daily/weekly (in future:
                               // biweekly/semimonthly/monthly/annual)
                               // note that the current API only supports daily
                               // or weekly alarm periods
  uint8_t isEnabled      :1 ;  // the timer is only actioned if isEnabled is true
  uint8_t isOneShot      :1 ;  // the timer will be de-allocated after trigger is processed
} AlarmMode_t;

// new time based alarms should be added just before dtLastAlarmType
typedef enum {
  dtNotAllocated,
  dtTimer,
  dtExplicitAlarm,
  dtDailyAlarm,
  dtWeeklyAlarm,
  dtLastAlarmType
} dtAlarmPeriod_t ; // in future: dtBiweekly, dtMonthly, dtAnnual

// macro to return true if the given type is a time based alarm, false if timer or not allocated
#define dtIsAlarm(_type_)  (_type_ >= dtExplicitAlarm && _type_ < dtLastAlarmType)
#define dtUseAbsoluteValue(_type_)  (_type_ == dtTimer || _type_ == dtExplicitAlarm)

typedef uint8_t AlarmID_t;
typedef AlarmID_t AlarmId;  // Arduino friendly name

#define dtINVALID_ALARM_ID 255
#define dtINVALID_TIME     (time_t)(-1)
#define AlarmHMS(_hr_, _min_, _sec_) (_hr_ * SECS_PER_HOUR + _min_ * SECS_PER_MIN + _sec_)

typedef void (*OnTick_t)();  // alarm callback function typedef

// class defining an alarm instance, only used by dtAlarmsClass
class AlarmClass
{
public:
  AlarmClass();
  OnTick_t onTickHandler;
  void updateNextTrigger();
  time_t value;
  time_t nextTrigger;
  int data; //parameter to store any data in the alarm
  AlarmMode_t Mode;
};

// class containing the collection of alarms
class TimeAlarmsClass
{
private:
 
  void serviceAlarms();
  uint8_t isServicing;
  uint8_t servicedAlarmId; // the alarm currently being serviced
  AlarmID_t create(time_t value, OnTick_t onTickHandler, uint8_t isOneShot, dtAlarmPeriod_t alarmType,int data);

public:
  AlarmClass Alarm[dtNBR_ALARMS];//changed to public so that directly can acces the alarms

  TimeAlarmsClass();
  // functions to create alarms and timers

  // trigger once at the given time in the future
  AlarmID_t triggerOnce(time_t value, OnTick_t onTickHandler, int data) {
    if (value <= 0) return dtINVALID_ALARM_ID;
    return create(value, onTickHandler, true, dtExplicitAlarm, data);
  }

  // trigger once at given time of day
  AlarmID_t alarmOnce(time_t value, OnTick_t onTickHandler,int data) {
    if (value <= 0 || value > SECS_PER_DAY) return dtINVALID_ALARM_ID;
    return create(value, onTickHandler, true, dtDailyAlarm, data);
  }
  AlarmID_t alarmOnce(const int H, const int M, const int S, OnTick_t onTickHandler,int data) {
    return alarmOnce(AlarmHMS(H,M,S), onTickHandler, data);
  }

  // trigger once on a given day and time
  AlarmID_t alarmOnce(const timeDayOfWeek_t DOW, const int H, const int M, const int S, OnTick_t onTickHandler, int data) {
    time_t value = (DOW-1) * SECS_PER_DAY + AlarmHMS(H,M,S);
    if (value <= 0) return dtINVALID_ALARM_ID;
    return create(value, onTickHandler, true, dtWeeklyAlarm, data);
  }

  // trigger daily at given time of day
  AlarmID_t alarmRepeat(time_t value, OnTick_t onTickHandler, int data) {
    if (value > SECS_PER_DAY) return dtINVALID_ALARM_ID;
    return create(value, onTickHandler, false, dtDailyAlarm, data);
  }
  AlarmID_t alarmRepeat(const int H, const int M, const int S, OnTick_t onTickHandler, int data) {
    return alarmRepeat(AlarmHMS(H,M,S), onTickHandler, data);
  }

  // trigger weekly at a specific day and time
  AlarmID_t alarmRepeat(const timeDayOfWeek_t DOW, const int H, const int M, const int S, OnTick_t onTickHandler, int data) {
    time_t value = (DOW-1) * SECS_PER_DAY + AlarmHMS(H,M,S);
    if (value <= 0) return dtINVALID_ALARM_ID;
    return create(value, onTickHandler, false, dtWeeklyAlarm, data);
  }

  // trigger once after the given number of seconds
  AlarmID_t timerOnce(time_t value, OnTick_t onTickHandler, int data) {
    if (value <= 0) return dtINVALID_ALARM_ID;
    return create(value, onTickHandler, true, dtTimer, data);
  }
  AlarmID_t timerOnce(const int H, const int M, const int S, OnTick_t onTickHandler, int data) {
    return timerOnce(AlarmHMS(H,M,S), onTickHandler, data);
  }

  // trigger at a regular interval
  AlarmID_t timerRepeat(time_t value, OnTick_t onTickHandler, int data) {
    if (value <= 0) return dtINVALID_ALARM_ID;
    return create(value, onTickHandler, false, dtTimer, data);
  }
  AlarmID_t timerRepeat(const int H,  const int M,  const int S, OnTick_t onTickHandler, int data) {
    return timerRepeat(AlarmHMS(H,M,S), onTickHandler, data);
  }

  void delay(unsigned long ms);

  // utility methods
  uint8_t getDigitsNow( dtUnits_t Units);         // returns the current digit value for the given time unit
  void waitForDigits( uint8_t Digits, dtUnits_t Units);
  void waitForRollover(dtUnits_t Units);

  // low level methods
  void enable(AlarmID_t ID);                // enable the alarm to trigger
  void disable(AlarmID_t ID);               // prevent the alarm from triggering
  AlarmID_t getTriggeredAlarmId();          // returns the currently triggered  alarm id
  bool getIsServicing();                    // returns isServicing
  void write(AlarmID_t ID, time_t value,int data);   // write the value (and enable) the alarm with the given ID
  time_t read(AlarmID_t ID);                // return the value for the given timer
  dtAlarmPeriod_t readType(AlarmID_t ID);   // return the alarm type for the given alarm ID

  void free(AlarmID_t ID);                  // free the id to allow its reuse

#ifndef USE_SPECIALIST_METHODS
private:  // the following methods are for testing and are not documented as part of the standard library
#endif
  uint8_t count();                          // returns the number of allocated timers
  time_t getNextTrigger();                  // returns the time of the next scheduled alarm
  bool isAllocated(AlarmID_t ID);           // returns true if this id is allocated
  bool isAlarm(AlarmID_t ID);               // returns true if id is for a time based alarm, false if its a timer or not allocated
};

extern TimeAlarmsClass Alarm;  // make an instance for the user

/*==============================================================================
 * MACROS
 *============================================================================*/

/* public */
#define waitUntilThisSecond(_val_) waitForDigits( _val_, dtSecond)
#define waitUntilThisMinute(_val_) waitForDigits( _val_, dtMinute)
#define waitUntilThisHour(_val_)   waitForDigits( _val_, dtHour)
#define waitUntilThisDay(_val_)    waitForDigits( _val_, dtDay)
#define waitMinuteRollover() waitForRollover(dtSecond)
#define waitHourRollover()   waitForRollover(dtMinute)
#define waitDayRollover()    waitForRollover(dtHour)


#endif /* TimeAlarms_h */

