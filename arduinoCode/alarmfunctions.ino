//void setupAlarms() {
//  AlarmClass memAlarm[dtNBR_ALARMS];
//
//  EEPROM.get(memAdress, memAlarm);
//  Serial.println("get Old fans");
//  Serial.println((String)memAlarm[0].Mode.alarmType);
//
//  if (memAlarm != NULL ) { //if is a valid alarmClass parameter
//
//    for (int i = 0; i < dtNBR_ALARMS; i++) {
//      Alarm.Alarm[i] = memAlarm[i];
//
//      if (Alarm.Alarm[i].Mode.isEnabled) { //setup or next trigger event
//        Alarm.enable(i);
//      }
//
//    }
//    
//  }
//}
//
//AlarmID_t setAlarm(StringSplitter *command ) {
//  AlarmID_t result;
//  if (command->getItemCount() == 4) {
//    result = setAlarm(command->getItemAtIndex(0).toInt(), command->getItemAtIndex(1).toInt(), command->getItemAtIndex(2).toInt(), onOrOff(command->getItemAtIndex(3)));
//  }
//  else if (command->getItemCount() == 5) {
//    result = setAlarm(command->getItemAtIndex(0).toInt(), command->getItemAtIndex(1).toInt(), command->getItemAtIndex(2).toInt(), command->getItemAtIndex(3).toInt(), onOrOff(command->getItemAtIndex(4)));
//  } else {
//
//    return -1;
//  }
//
//  saveFans();
//
//  return result;
//}
//
//
//
//boolean onOrOff(String input) {
//  input.toLowerCase();
//  if (input.equals(ON_COMMAND)) {
//    return true;
//  } else {
//    return false;
//  }
//}
//
//String onOrOff(boolean input) { //inverse
//  if (input) {
//    return ON_COMMAND;
//  } else {
//    return OFF_COMMAND;
//  }
//}
//
//AlarmID_t setAlarm(int Hour, int Minute, int Second, boolean on) {
//  AlarmID_t id;
//  if (on) {
//    id = Alarm.alarmRepeat(Hour, Minute, Second, fanOn);
//  } else {
//    id = Alarm.alarmRepeat(Hour, Minute, Second, fanOff);
//  }
//  //alarms.pop_front(id);
//  return id;
//}
//
//AlarmID_t setAlarm(int DayOfWeek, int Hour, int Minute, int Second, boolean on) {
//  AlarmID_t id;
//  if (on) {
//    id = Alarm.alarmRepeat(DayOfWeek, Hour, Minute, Second, fanOn);
//  } else {
//    id = Alarm.alarmRepeat(DayOfWeek, Hour, Minute, Second, fanOff);
//  }
//
//  return id;
//}
//AlarmID_t setTimerOnce(int Hour, int Minute, int Second, boolean on) {
//  AlarmID_t id;
//  if (on) {
//    id = Alarm.timerOnce( Hour, Minute, Second, fanOn);
//  } else {
//    id = Alarm.timerOnce( Hour, Minute, Second, fanOff);
//  }
//  return id;
//}
//
//
//AlarmID_t setTimer(int Hour, int Minute, int Second, boolean on) {
//  AlarmID_t id;
//  if (on) {
//    id = Alarm.timerRepeat( Hour, Minute, Second, fanOn);
//  } else {
//    id = Alarm.timerRepeat( Hour, Minute, Second, fanOff);
//  }
//  return id;
//}
//
//void removeTimer(AlarmID_t id) {
//  Alarm.free(id);
//  saveFans();
//
//}
//
//boolean saveFans() {
//  //save fans to memory
//  return EEPROM.put(memAdress, Alarm.Alarm);
//}
//
//

