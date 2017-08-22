
#include "FansController.h"

FansController::FansController() {
  Serial.println("fans controller init");
  //set fan control pin
  pinMode(FAN_PIN, OUTPUT);

}


static void FansController::on() {
  fan(255);
}

static void FansController::off() {
  fan(0);
}


static void FansController::fan(int speed) {
  fanOn = (speed > 0);
  analogWrite(FAN_PIN, speed);
}

void FansController::setSpeed(int _speed) {
  speed = _speed;
}

void FansController::getSpeed() {
  return speed;
}


void FansController::onOff() {
  oldFanOn = fanOn;
  if (fanOn) {
    off();
  } else {
    on();
  }
  onOfEnabled = true;
  onOfTimer = millis();
}

void FansController::loop() {

  if (onOfEnabled && onOfTimer + INBETWEEN_ON_OF < millis()) {
    onOfEnabled = false;
    fan(oldFanOn);//reset to previous state
  }

}



