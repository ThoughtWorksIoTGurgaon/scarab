#include "DeviceCharacteristic.h"
#include "DeviceService.h"
void DeviceCharacteristic :: write(int, char *, int (* digitalWriteCallback)(int, int)){

}

char* DeviceCharacteristic::read(){
  int dataLen = sizeof(DeviceService::serviceIdProfileMap);
  int structLen = sizeof(ServiceIdProfileMap);

  char count = (int) dataLen/structLen;

  char *data = new char[1 + dataLen];
  data[0] = count * 2;

  Serial.println("(int)data[0]");
  Serial.println((int)data[0]);


  for (int i = 0; i < count; i++) {
    char pId = DeviceService::serviceIdProfileMap[i].serviceProfileId + 1;
    char sId = DeviceService::serviceIdProfileMap[i].serviceId + 1;

    data[1 + i*2 + 0] = pId;
    data[1 + i*2 + 1] = sId;
  }

  return data;
}
