#define FAN_PIN 16 //pin A2

void setup() {
  // put your setup code here, to run once:
  pinMode(FAN_PIN,OUTPUT);

}

void loop() {
  analogWrite(FAN_PIN,255);
  delay(1000);
}
