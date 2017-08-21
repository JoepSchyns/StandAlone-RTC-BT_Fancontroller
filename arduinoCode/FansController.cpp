
#include "FansController.h"

FansController::FansController() {
  Serial.println("fans controller init");
  //set fan control pin
  pinMode(FAN_PIN, OUTPUT);

}

static void FansController::on() {
  fan(true);
}

static void FansController::off() {
  fan(false);
}


static void FansController::fan(boolean on) {
  fanOn = on;
  Serial.print("fan on: ");
  Serial.println(on);
  if (on) {
    analogWrite(FAN_PIN, speed);
  } else {
    analogWrite(FAN_PIN, 0);
  }
}

void FansController::setSpeed(int _speed){
  speed = _speed;
}

void FansController::getSpeed(){
  return speed;
}


void FansController::onOf(){
  on();
  onOfEnabled = true;
  onOfTimer = millis();
}

void FansController::loop(){

  if(onOfEnabled && onOfTimer + INBETWEEN_ON_OF < millis()){
    onOfEnabled = false;
    off();
  }
  
}

