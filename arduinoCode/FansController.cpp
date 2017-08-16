
#include "FansController.h"

FansController::FansController() {
  Serial.println("fans controller init");
  //set fan control pin
  pinMode(FAN_PIN, OUTPUT);
}

void static FansController::on() {
  fan(true);
}
void static FansController::off() {
  fan(false);
}

void static FansController::fan(boolean on) {
  Serial.print("fan on: ");
  Serial.println(on);
  if (on) {
    digitalWrite(FAN_PIN, 255);
  } else {
    digitalWrite(FAN_PIN, 0);
  }
}

