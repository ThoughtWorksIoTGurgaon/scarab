#include "DeviceCharacteristic.h"
#include "DeviceService.h"
void DeviceCharacteristic :: write(int, char *, int (* digitalWriteCallback)(int, int)){

}

char* DeviceCharacteristic::read(){
  int structLen = sizeof(ServiceIdProfileStruct);
  char count = deviceService.noOfServiceInstancePresent;
  int dataLen = structLen * count;

  char *data = new char[1 + dataLen];
  data[0] = count * 2;

  for (int i = 0; i < count; i++) {
    ServiceIdProfileStruct entry = deviceService.getServiceIdProfile(i);
    char pId = entry.serviceProfileId + 1;
    char sId = entry.serviceId + 1;

    data[1 + i*2 + 0] = pId;
    data[1 + i*2 + 1] = sId;
  }

  return data;
}
