
AlarmID_t setAlarm(StringSplitter *command ){
  if(command->getItemCount() == 4){
    return setAlarm(command->getItemAtIndex(0).toInt(),command->getItemAtIndex(1).toInt(),command->getItemAtIndex(2).toInt(),onOrOff(command->getItemAtIndex(3)));
  }
  else if(command->getItemCount() == 5){
    return setAlarm(command->getItemAtIndex(0).toInt(),command->getItemAtIndex(1).toInt(),command->getItemAtIndex(2).toInt(),command->getItemAtIndex(3).toInt(),onOrOff(command->getItemAtIndex(4)));
  }
  return "-1";
}

const String ON_COMMAND = "on";

boolean onOrOff(String input){
  input.toLowerCase();
  if(input.equals(ON_COMMAND)){
    return true;
  }else{
    return false;
  }
}

AlarmID_t setAlarm(int Hour,int Minute,int Second,boolean on){
  AlarmID_t id;
  if(on){
    id = Alarm.alarmRepeat(Hour, Minute, Second, fanOn);
  }else{
    id = Alarm.alarmRepeat(Hour, Minute, Second, fanOff);
  }
  //alarms.pop_front(id);
  return id;
}

AlarmID_t setAlarm(int DayOfWeek,int Hour,int Minute,int Second,boolean on){
  AlarmID_t id;
  if(on){
    id = Alarm.alarmRepeat(DayOfWeek, Hour, Minute, Second, fanOn);
  }else{
    id = Alarm.alarmRepeat(DayOfWeek, Hour, Minute, Second, fanOff);
  }
  
  //alarms.pop_front(id);
  return id;
}
AlarmID_t setTimerOnce(int Hour,int Minute,int Second,boolean on){
  AlarmID_t id;
  if(on){
    id = Alarm.timerOnce( Hour, Minute,Second, fanOn);
  }else{
    id = Alarm.timerOnce( Hour, Minute,Second, fanOff);
  }
  
  //alarms.pop_front(id);
  return id;
}


AlarmID_t setTimer(int Hour,int Minute,int Second,boolean on){
  AlarmID_t id;
  if(on){
    id = Alarm.timerRepeat( Hour, Minute,Second, fanOn);
  }else{
    id = Alarm.timerRepeat( Hour, Minute,Second, fanOff);
  }
  
  //alarms.pop_front(id);
  return id;
}



