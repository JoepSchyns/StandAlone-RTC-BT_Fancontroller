#define FAN_PIN 4 //pin A2

void setupFan(){
  //set fan control pin
  pinMode(FAN_PIN,OUTPUT);
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
