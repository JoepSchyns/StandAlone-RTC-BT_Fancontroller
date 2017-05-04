

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








