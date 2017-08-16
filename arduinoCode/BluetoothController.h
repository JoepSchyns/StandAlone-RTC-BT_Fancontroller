
#ifndef BluetoothController_h
#define BluetoothController_h

#include <Arduino.h>

#include "AlarmController.h"
#include "FansController.h"
#include "RTCController.h"

//bluetooth libaries
#include <SoftwareSerial.h>

#include <StringSplitter.h>

//TODO FIX WHY WONT THIS COMPILE
#define BLUETOOTH_RX 5
#define BLUETOOTH_TX 6

class BluetoothController {
  private:
    const String OK_RESULT = "+OK";
    const String ERROR_RESULT = "+ERROR";
    const String MAX_FANS_RESULT = "+MAX_FANS_ERROR";

    const String FAN_ON = "fanOn";
    const String FAN_OFF = "fanOff";
    const String SET_FAN = "setFan";
    const String SET_TIMER_FAN = "setTimerFan";
    const String SET_TIME = "setTime";
    const String GET_FANS = "getFans";
    const String GET_TIME = "getTime";
    const String REMOVE_FAN = "removeFan";
    const String REMOVE_FANS = "removeFans";

    const int NO_COMMUNICATION_TIME = 50;
    unsigned long inbetweenTime;
    boolean bluetoothCommunication;

    SoftwareSerial *bluetoothSerial = new SoftwareSerial(5,6);
    String bluetoothRead = "";

    void action(String input);
    String fanCodeToString(int code);

    AlarmController alarmController;
    FansController fansController;
    RTCController rtcController;

  public:
    BluetoothController();
    void loopBluetooth();

};

#endif

