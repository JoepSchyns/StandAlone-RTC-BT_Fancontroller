
#ifndef FansController_h
#define FansController_h

#include "Arduino.h"

#define FAN_PIN 10 //pin A2

class FansController {
  private:
    static void fan(boolean on);
    unsigned long onOfTimer;
    const int INBETWEEN_ON_OF = 300;
    boolean onOfEnabled;
  public:
    FansController();
    static boolean fanOn;
    static void on();
    static void off();
    static void setSpeed(int _speed);
    static void getSpeed();
    static int speed;
    
    void loop();
    void onOf();
    
};


#endif


