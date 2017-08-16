

#include "BluetoothController.h"
BluetoothController *bluetoothController;



void setup() {
  Serial.begin(9600);
   while (!Serial){
    Serial.println("waiting for serial");
   }
   Serial.println("Start program");
   bluetoothController = new BluetoothController();
  
}


void loop() {
  bluetoothController->loopBluetooth();
  
}








