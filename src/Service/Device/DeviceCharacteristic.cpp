#include "DeviceCharacteristic.h"
#include "DeviceService.h"
void DeviceCharacteristic :: write(int, byte *, int (* digitalWriteCallback)(int, int)){

}

byte* DeviceCharacteristic::read(){
  int structLen = sizeof(ServiceIdProfileStruct);
  char count = deviceService.noOfServiceInstancePresent;
  int dataLen = structLen * count;

  byte *data = new byte[1 + dataLen];
  data[0] = count * 2;

  for (int i = 0; i < count; i++) {
    ServiceIdProfileStruct entry = deviceService.getServiceIdProfile(i);
    byte pId = entry.serviceProfileId + 1;
    byte sId = entry.serviceId + 1;

    data[1 + i*2 + 0] = pId;
    data[1 + i*2 + 1] = sId;
  }

  return data;
}
