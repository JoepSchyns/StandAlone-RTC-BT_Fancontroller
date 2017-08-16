
#ifndef FansController_h
#define FansController_h

#include "Arduino.h"

#define FAN_PIN 4 //pin A2

class FansController {
  private:
    void static fan(boolean on);

  public:
    FansController();
    void static on();
    void static off();


};


#endif


