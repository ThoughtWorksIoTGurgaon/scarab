#include "DeviceService.h"
#include "DeviceCharacteristic.h"
ServiceIdProfileMap DeviceService :: serviceIdProfileMap[2];
Characteristic** DeviceService :: construct(int *port){
  return new Characteristic*[1]{
      new DeviceCharacteristic()
  };
}
