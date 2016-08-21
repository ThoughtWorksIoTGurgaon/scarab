#include "SwitchService.h"
#include "SwitchCharacteristic.h"

Characteristic** SwitchService::construct(int *port){
  Characteristic ** chars = new Characteristic*[1];
  chars[0] = new SwitchCharacteristic(port[0]);
  return chars;
}
