
#define BLUETOOTH_RX 10
#define BLUETOOTH_TX 11

#define NO_COMMUNICATION_TIME 50
unsigned long inbetweenTime;

SoftwareSerial bluetoothSerial(BLUETOOTH_RX, BLUETOOTH_TX); // RX, TX
String bluetoothRead = "";

void setupBluetooth(){
  
  bluetoothSerial.begin(9600);
  
}

void loopBluetooth(){
  if (bluetoothSerial.available()){
    inbetweenTime = millis();
    bluetoothCommunication = true;
    bluetoothRead.concat((char)bluetoothSerial.read());
  }

  if(bluetoothCommunication && millis() > (NO_COMMUNICATION_TIME + inbetweenTime)){
    Serial.println("communication done");
    bluetoothRead.trim();
    Serial.println(bluetoothRead);
    action(bluetoothRead);
    bluetoothRead = "";
    bluetoothCommunication = false;
  }
    
  if (Serial.available()) {
    bluetoothSerial.write(Serial.read());//comunicate to bluetoothchip
  }
}
const String FAN_ON = "fanOn";
const String FAN_OFF = "fanOff";
const String SET_FAN = "setFan";
const String SET_TIME = "setTime";

void action(String input){
  if(input.equals(FAN_ON)){
    fanOn();
    sendBluetooth(FAN_ON + "+OK");
  }
  else if(input.equals(FAN_OFF)){
    fanOff();
    sendBluetooth(FAN_OFF + "+OK");
  }
  else if(input.substring(0,SET_FAN.length()).equals(SET_FAN)){
    
    String result = setFan(input);
    
    sendBluetooth(result);
    
  }else if(input.substring(0,SET_TIME.length()).equals(SET_TIME)){
    setDate(input);
    
    DateTime now = rtc.now();
    
    String result = "Date: " + now.year(); 
    result += ":" + now.month(); 
    result += ":" + now.day(); 
    result += ":" + now.hour(); 
    result += ":" + now.minute(); 
    result += ":" + now.second();
    
    sendBluetooth(result);
  }
  
  else{
     sendBluetooth("unknown command");
  }
}

void setDate(String input){
  String commandString = input.substring(SET_TIME.length());
  StringSplitter *command = new StringSplitter(commandString, ':', 7);
  adjustRTC(command->getItemAtIndex(0).toInt(),
  command->getItemAtIndex(1).toInt(),
  command->getItemAtIndex(2).toInt(),
  command->getItemAtIndex(3).toInt(),
  command->getItemAtIndex(4).toInt(),
  command->getItemAtIndex(5).toInt());
}

String setFan(String input){
  
  String commandString = input.substring(SET_FAN.length());
    StringSplitter *command = new StringSplitter(commandString, ':', 6);
    AlarmID_t alarmID = setAlarm(command);

    String result = "ID: " + (String)alarmID;
    result += " Value: "  + (String)Alarm.read(alarmID);
    result += " Type: " + (String)Alarm.readType(alarmID);
    
    return result;
}

void sendBluetooth(String text){
  bluetoothSerial.println(text);//comunicate to bluetoothchip
}



