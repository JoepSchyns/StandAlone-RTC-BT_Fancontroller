#include "Arduino.h"
#include "AlarmController.h"

AlarmController::AlarmController() {
  Serial.println("alarm controller init");
  AlarmClass memAlarm[dtNBR_ALARMS];

  EEPROM.get(memAdress, memAlarm);

  if (memAlarm != NULL ) { //if is a valid alarmClass parameter

    for (int i = 0; i < dtNBR_ALARMS; i++) {
      Alarm.Alarm[i] = memAlarm[i];

      if (Alarm.Alarm[i].Mode.isEnabled) { //setup or next trigger event
        Alarm.enable(i);
      }

    }
  }
}


int AlarmController::setAlarm(StringSplitter *command) {
  int result;

  if (Alarm.count() >= dtNBR_ALARMS) { //if is smaller than maximum amount of alarms
    return -2;
  }

  if (command->getItemCount() == 4) {
    result = setAlarm(command->getItemAtIndex(0).toInt(), command->getItemAtIndex(1).toInt(), command->getItemAtIndex(2).toInt(), onOrOff(command->getItemAtIndex(3)));
  }
  else if (command->getItemCount() == 5) {
    result = setAlarm(command->getItemAtIndex(0).toInt(), command->getItemAtIndex(1).toInt(), command->getItemAtIndex(2).toInt(), command->getItemAtIndex(3).toInt(), onOrOff(command->getItemAtIndex(4)));
  }
  else {

    return -1; //no such command for setting a alarm found
  }

  saveAlarms();
  return result;
}

int AlarmController::setAlarm(int Hour, int Minute, int Second, boolean on) {
  int id;
  if (on) {
    id = Alarm.alarmRepeat(Hour, Minute, Second, FansController::on);
  } else {
    id = Alarm.alarmRepeat(Hour, Minute, Second, FansController::off);
  }
  return id;
}

int AlarmController::setAlarm(int DayOfWeek, int Hour, int Minute, int Second, boolean on) {
  int id;
  if (on) {
    id = Alarm.alarmRepeat(DayOfWeek, Hour, Minute, Second, FansController::on);
  } else {
    id = Alarm.alarmRepeat(DayOfWeek, Hour, Minute, Second, FansController::off);
  }

  return id;
}

int AlarmController::setTimer(StringSplitter *command ) {
  if (Alarm.count() < dtNBR_ALARMS - 1) { //if is smaller than maximum amount of alarms
    return -2;
  }
  else if (command->getItemCount() == 4) {
    setTimer(command->getItemAtIndex(0).toInt(), command->getItemAtIndex(1).toInt(), command->getItemAtIndex(2).toInt(), onOrOff(command->getItemAtIndex(3)));
  }
  else {
    return -1; //to such command
  }
}

int AlarmController::setTimer(int Hour, int Minute, int Second, boolean on) {
  int id;
  if (on) {
    id = Alarm.timerRepeat( Hour, Minute, Second, FansController::on);
  } else {
    id = Alarm.timerRepeat( Hour, Minute, Second, FansController::off);
  }
  return id;
}

void AlarmController::removeAlarms() {
  for (int id = 0; id < dtNBR_ALARMS; id++) {
    Alarm.free(id);
    removeAlarm(id);
  }
  saveAlarms();
}

void AlarmController::removeAlarm(int id) {
  Alarm.free(id);
  saveAlarms();
}

boolean AlarmController::saveAlarms() {
  //save fans to memory
  return EEPROM.put(memAdress, Alarm.Alarm);
}

String AlarmController::alarmInfo(int ID) {
  String result = "Fan;"+(String)ID;// + ";" + (String)Alarm.Alarm[ID].Mode.isEnabled + ";" + Alarm.Alarm[ID].Mode.alarmType + ";" + RTCController::time_tReadable(Alarm.Alarm[ID].value);


    result += ";" + (String)Alarm.Alarm[ID].Mode.isEnabled;
    result += ";" + (String)Alarm.Alarm[ID].Mode.alarmType;
    result += ";" + RTCController::time_tReadable(Alarm.Alarm[ID].value);
   // result += " nextTrigger: " + RTCController::time_tReadable(Alarm.Alarm[ID].nextTrigger);

  return result;
}

boolean AlarmController::onOrOff(String input) {
  input.toLowerCase();
  if (input.equals(ON_COMMAND)) {
    return true;
  } else {
    return false;
  }
}

String AlarmController::onOrOff(boolean input) { //inverse
  if (input) {
    return ON_COMMAND;
  } else {
    return OFF_COMMAND;
  }
}

void AlarmController::delay(int time) {
  Alarm.delay(time);
}

int AlarmController::count() {
  return Alarm.count();
}


