

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
  //Serial.println(freeRam()); //memory leak checker
  
}

int freeRam ()
{
extern int __heap_start, *__brkval;
int v;
return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}








