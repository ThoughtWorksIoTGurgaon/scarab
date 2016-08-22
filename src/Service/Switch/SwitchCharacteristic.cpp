#include "SwitchCharacteristic.h"
#define HIGH 1
#define LOW 0

SwitchCharacteristic :: SwitchCharacteristic(int port) : Characteristic(port){}
void SwitchCharacteristic::write(int dataLen, byte *data, int (* digitalWriteCallback)(int, int)) {
    if(data[0] == ON) {
      if(HIGH == digitalWriteCallback(portNumber, HIGH)){
          status = "H";
      }
    }
    else if(data[0] == OFF) {
      if(LOW == digitalWriteCallback(portNumber, LOW)){
          status = "L";
      }
    }
}
