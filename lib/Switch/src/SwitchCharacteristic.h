#ifndef SWITCH_CHARACTERISTIC_H
#define SWITCH_CHARACTERISTIC_H
#include "Characteristic.h"
#include "Arduino.h"

class SwitchCharacteristic : public Characteristic{
  public :
    SwitchCharacteristic(int portNumber);
    void write(int, char *, int (* digitalWriteCallback)(int, int)) ;
    char* read(){ Serial.println("__________NOT IMPLEMENTED________");}
};

#endif
