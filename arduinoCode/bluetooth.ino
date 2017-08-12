
#define BLUETOOTH_RX 5
#define BLUETOOTH_TX 6

#define NO_COMMUNICATION_TIME 50
unsigned long inbetweenTime;

SoftwareSerial bluetoothSerial(BLUETOOTH_RX, BLUETOOTH_TX); // RX, TX
String bluetoothRead = "";

void setupBluetooth() {

  bluetoothSerial.begin(9600);

}

void loopBluetooth() {
  if (bluetoothSerial.available()) {
    inbetweenTime = millis();
    bluetoothCommunication = true;
    bluetoothRead.concat((char)bluetoothSerial.read());
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
    bluetoothSerial.write(Serial.read());//comunicate to bluetoothchip
  }
}
const String FAN_ON = "fanOn";
const String FAN_OFF = "fanOff";
const String SET_FAN = "setFan";
const String SET_TIME = "setTime";
const String GET_FANS = "getFans";
const String GET_TIME = "getTime";
const String REMOVE_FAN = "removeFan";

void action(String input) {
  if (input.equals(FAN_ON)) {
    fanOn();
    sendBluetooth(FAN_ON + "+OK");
  }
  else if (input.equals(FAN_OFF)) {
    fanOff();
    sendBluetooth(FAN_OFF + "+OK");
  }
  else if (input.equals(GET_TIME)) {
    String sender = timeString();
    sendBluetooth(sender);
  }
  else if (input.equals(GET_FANS)) {
    for (int i = 0; i < (int)Alarm.count(); i++) {
      String sender = "Alarm " + (String)fans[i].id;
      sender += " time: " + time_tReadable(fans[i].value);
      sender += " type: " + (String)fans[i].type;
      sendBluetooth(sender);
    }
  }
  else if (input.substring(0, SET_FAN.length()).equals(SET_FAN)) {

    String result = setFan(input);

    sendBluetooth(result);

  }
  else if (input.substring(0, REMOVE_FAN.length()).equals(REMOVE_FAN)) {

    String commandString = input.substring(REMOVE_FAN.length());
    removeTimer((AlarmID_t)commandString.toInt());

    AlarmID_t alarmID = (AlarmID_t)commandString.toInt();
    String result = "ID: " + (String)alarmID;
    result += " Value: "  + time_tReadable(Alarm.read(alarmID));
    result += " Type: " + (String)Alarm.readType(alarmID);


    sendBluetooth(result);

  }
  else if (input.substring(0, SET_TIME.length()).equals(SET_TIME)) {
    setDate(input);

    String sender = timeString();
    sendBluetooth(sender);
  }

  else {
    sendBluetooth("unknown command");
  }
}

void setDate(String input) {
  String commandString = input.substring(SET_TIME.length());
  StringSplitter *command = new StringSplitter(commandString, ':', 7);
  adjustRTC(command->getItemAtIndex(0).toInt(),
            command->getItemAtIndex(1).toInt(),
            command->getItemAtIndex(2).toInt(),
            command->getItemAtIndex(3).toInt(),
            command->getItemAtIndex(4).toInt(),
            command->getItemAtIndex(5).toInt());
}
/*
  String setFan(String input){

  String commandString = input.substring(SET_FAN.length());
    StringSplitter *command = new StringSplitter(commandString, ':', 6);
    AlarmID_t alarmID = setAlarm(command);

    String result = "ID: " + (String)alarmID;
    result += " Value: "  + time_tReadable(Alarm.read(alarmID));
    result += " Type: " + (String)Alarm.readType(alarmID);

    return result;
  }**/

String setFan(String input) {

  String result = "";

  int amountOfAlarms = (int)Alarm.count();
  if (amountOfAlarms < dtNBR_ALARMS) //if is smaller than maximum amount of alarms
  {
    String commandString = input.substring(SET_FAN.length());
    StringSplitter *command = new StringSplitter(commandString, ':', 6);
    AlarmID_t alarmID = setAlarm(command);


    fans[amountOfAlarms].id = alarmID;
    fans[amountOfAlarms].value = Alarm.read(alarmID);
    fans[amountOfAlarms].type = Alarm.readType(alarmID);

    result += "ID: " + (String)fans[amountOfAlarms].id;
    result += " Value: "  + time_tReadable(fans[amountOfAlarms].value);
    result += " Type: " + (String)fans[amountOfAlarms].type;

  } else
  {
    result += "Max amount of fans(" + (String)dtNBR_ALARMS + ") is reached please remove one before adding a new fan";
  }

  return result;
}

void sendBluetooth(String text) {
  bluetoothSerial.println(text);//comunicate to bluetoothchip
}



