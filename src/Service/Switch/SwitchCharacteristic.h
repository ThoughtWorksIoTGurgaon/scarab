#ifndef SWITCH_CHARACTERISTIC_H
#define SWITCH_CHARACTERISTIC_H
#include <Characteristic.h>

class SwitchCharacteristic : public Characteristic{
  public :
    SwitchCharacteristic(int portNumber);
    void write(int, char *, int (* digitalWriteCallback)(int, int)) ;
    char* read(){ return "__________NOT IMPLEMENTED________";}
};

#endif
