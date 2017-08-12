

//timer libaries
#include <Time.h>
#include <TimeAlarms.h> //https://github.com/PaulStoffregen/TimeAlarms

//rtc libaries
#include <Wire.h>
#include "RTClib.h"

//bluetooth libaries
#include <SoftwareSerial.h>
#include <StringSplitter.h>

#include <EEPROM.h>


boolean bluetoothCommunication = false;

struct AlarmInfo{
  AlarmID_t id;
  time_t value;
  dtAlarmPeriod_t type;
};

static const struct AlarmInfo EmptyAlarmInfo;

struct AlarmInfo fans[dtNBR_ALARMS]; //save the alarms


void setup() {
  Serial.begin(9600);
  
  setupFan();
  setupRTC();
  setupBluetooth();

  //test timer
//  Serial.println(setTimer(0,0,10,true));
//  Serial.println(setTimer(0,0,15,false));


}


void loop() {
    
  loopBluetooth();
  
  
  if(bluetoothCommunication){
    Alarm.delay(0);
  }else{
    printTime();
    Alarm.delay(1000);
  }
  
}








