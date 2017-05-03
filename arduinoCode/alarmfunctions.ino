


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

void fanOn(){
  fan(true);
}
void fanOff(){
  fan(false);
}

void fan(boolean on){
  Serial.print("fan on: ");
  Serial.println(on);
  if(on){
    digitalWrite(FAN_PIN,255);
  }else{
    digitalWrite(FAN_PIN,0);
  }
}

