#include <Wire.h>
#include "RTClib.h"

#include <Time.h>
#include <TimeAlarms.h> //https://github.com/PaulStoffregen/TimeAlarms

RTC_DS3231 rtc;

//#include <QList.h> //https://github.com/SloCompTech/QList

#define FAN_PIN 16 //pin A2

//QList<AlarmID_t> alarms;

void setup() {
  Serial.begin(9600);
  setTime(8,29,0,1,1,11); // set time to Saturday 8:29:00am Jan 1 2011
  
  //set fan control pin
  pinMode(FAN_PIN,OUTPUT);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  setSyncProvider(syncProvider);   // the function to get the time from the RTC
  if(timeStatus()!= timeSet) 
    Serial.println("Unable to sync with the RTC");
  else
    Serial.println("RTC has set the system time");  
  setSyncInterval(10000); // set the number of seconds between re-sync of time

  Serial.println(setAlarm(1,1,1,true));
  Serial.println(setAlarm(1,1,2,false));
  Serial.println( setTimer(0,0,1,true));
  Serial.println(setTimer(0,0,2,false));
  fanOn();



}


void loop() {
  
  printTime();
  delay(1000);
  
}

AlarmID_t setAlarm(int Hour,int Minute,int Second,boolean on){
  AlarmID_t id;
  if(on){
    id = Alarm.alarmRepeat(Hour, Minute, Second, fanOn);
  }else{
    id = Alarm.alarmRepeat(Hour, Minute, Second, fanOff);
  }
  //alarms.pop_front(id);
  return id;
}

AlarmID_t setAlarm(int DayOfWeek,int Hour,int Minute,int Second,boolean on){
  AlarmID_t id;
  if(on){
    id = Alarm.alarmRepeat(DayOfWeek, Hour, Minute, Second, fanOn);
  }else{
    id = Alarm.alarmRepeat(DayOfWeek, Hour, Minute, Second, fanOff);
  }
  
  //alarms.pop_front(id);
  return id;
}

AlarmID_t setTimer(int Hour,int Minute,int Second,boolean on){
  AlarmID_t id;
  if(on){
    id = Alarm.timerRepeat(Second, fanOn);
  }else{
    id = Alarm.timerRepeat(Second, fanOff);
  }
  
  //alarms.pop_front(id);
  return id;
}

void fanOn(){
  fan(true);
}
void fanOff(){
  fan(false);
}

void fan(boolean on){
  Serial.print("fan on: ");
  Serial.println(on);
  if(on){
    digitalWrite(FAN_PIN,255);
  }else{
    digitalWrite(FAN_PIN,0);
  }
}

void printTime(){
  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
}

uint32_t syncProvider(){//function which sets up the RTC as the source of external time
  return rtc.now().unixtime();
}





