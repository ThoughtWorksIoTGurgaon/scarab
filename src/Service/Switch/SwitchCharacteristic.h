#ifndef SWITCH_CHARACTERISTIC_H
#define SWITCH_CHARACTERISTIC_H
#include <Characteristic.h>

class SwitchCharacteristic : public Characteristic{
  public :
    SwitchCharacteristic(int portNumber);
    void write(int, byte *, int (* digitalWriteCallback)(int, int)) ;
    byte* read(){ return 0;}
};

#endif
