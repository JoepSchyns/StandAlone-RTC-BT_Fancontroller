#include <Time.h>
#include <TimeAlarms.h> //https://github.com/PaulStoffregen/TimeAlarms
#include <Wire.h>
#include "RTClib.h"

//#include <QList.h> //https://github.com/SloCompTech/QList

#define FAN_PIN 16 //pin A2

//QList<AlarmID_t> alarms;

void setup() {
  Serial.begin(9600);
  
  //set fan control pin
  pinMode(FAN_PIN,OUTPUT);

  setupRTC();

  //test timer
  Serial.println(setTimer(0,0,10,true));
  Serial.println(setTimer(0,0,15,false));


}


void loop() {
  
  printTime();
  Alarm.delay(1000);
  
}








