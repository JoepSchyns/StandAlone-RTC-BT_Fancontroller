
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

