#include "BluetoothController.h"

BluetoothController::BluetoothController() {
  
  Serial.println("test2");
  bluetoothSerial->begin(9600);
}

void BluetoothController::loopBluetooth() {
  if (bluetoothSerial->available()) {
    inbetweenTime = millis();
    bluetoothCommunication = true;
    bluetoothRead.concat((char)bluetoothSerial->read());
  }

  if (bluetoothCommunication && millis() > (NO_COMMUNICATION_TIME + inbetweenTime)) {
    Serial.println("communication done");
    bluetoothRead.trim();
    Serial.println(bluetoothRead);
    action(bluetoothRead);
    bluetoothRead = "";
    bluetoothCommunication = false;
  }

  if (Serial.available()) {
    bluetoothSerial->write(Serial.read());//comunicate to bluetoothchip
  }

  if (bluetoothCommunication) { //if there is bluetooth comminication dont sleep for a second
    alarmController.delay(0);
  } else {
    rtcController.printTime();
    alarmController.delay(1000);
  }
}

void BluetoothController::action(String input)
{
  if (input.equals(FAN_ON)) {
    fansController.on();
    bluetoothSerial->println(FAN_ON + OK_RESULT);
  }
  else if (input.equals(FAN_OFF))
  {
    fansController.off();
    bluetoothSerial->println(FAN_OFF + OK_RESULT);
  }
  else if (input.equals(GET_TIME))
  {
    String result = rtcController.timeString();
    bluetoothSerial->println(result);
  }
  else if (input.equals(GET_FANS))
  {
    String result = alarmController.getAlarms();
    bluetoothSerial->println(result);
  }
  else if (input.substring(0, SET_FAN.length()).equals(SET_FAN))
  {
    String commandString = input.substring(SET_FAN.length());
    StringSplitter *command = new StringSplitter(commandString, ':', 6);

    int code = alarmController.setAlarm(command);

    if (code == -1) {
      bluetoothSerial->println(SET_FAN + ERROR_RESULT);
    } else if (code == -2) {
      bluetoothSerial->println(SET_FAN + MAX_FANS_RESULT);
    } else {
      bluetoothSerial->println(SET_FAN + OK_RESULT + "+" + alarmController.alarmInfo(code));
    }
  }
  else if (input.substring(0, SET_FAN.length()).equals(SET_FAN))
  {
    String commandString = input.substring(SET_FAN.length());
    StringSplitter *command = new StringSplitter(commandString, ':', 6);

    int code = alarmController.setAlarm(command);
    String result = fanCodeToString(code);
    bluetoothSerial->println(result);
  }
  else if (input.substring(0, SET_TIMER_FAN.length()).equals(SET_TIMER_FAN))
  {
    String commandString = input.substring(SET_TIMER_FAN.length());
    StringSplitter *command = new StringSplitter(commandString, ':', 6);

    int code = alarmController.setTimer(command);
    String result = fanCodeToString(code);
    bluetoothSerial->println(result);
  }
  else if (input.substring(0, REMOVE_FAN.length()).equals(REMOVE_FAN))
  {
    String commandString = input.substring(REMOVE_FAN.length());
    int ID = commandString.toInt();
    alarmController.removeAlarm(ID);

    bluetoothSerial->println(REMOVE_FAN + ID + OK_RESULT);
  }
  else if (input.substring(0, REMOVE_FANS.length()).equals(REMOVE_FANS))
  {
    alarmController.removeAlarms();
    bluetoothSerial->println(REMOVE_FANS + OK_RESULT);
  }
  else if (input.substring(0, SET_TIME.length()).equals(SET_TIME))
  {
    String commandString = input.substring(SET_TIME.length());
    StringSplitter *command = new StringSplitter(commandString, ':', 7);
    rtcController.adjustRTC(command);
    String result = rtcController.timeString();
    bluetoothSerial->println(result);
  }
  else
  {
    bluetoothSerial->println("unknown command");
  }
}

String BluetoothController::fanCodeToString(int code) {
  if (code == -1) {
    bluetoothSerial->println(SET_FAN + ERROR_RESULT);
  } else if (code == -2) {
    bluetoothSerial->println(SET_FAN + MAX_FANS_RESULT);
  } else {
    bluetoothSerial->println(SET_FAN + OK_RESULT + "+" + alarmController.alarmInfo(code));
  }
}




