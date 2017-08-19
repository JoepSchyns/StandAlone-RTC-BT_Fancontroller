
#ifndef FansController_h
#define FansController_h

#include "Arduino.h"

#define FAN_PIN 10 //pin A2

class FansController {
  private:
    static void fan(boolean on);
  public:
    FansController();
    static void on();
    static void off();
    static void setSpeed(int _speed);
    static int speed;
    
};


#endif


