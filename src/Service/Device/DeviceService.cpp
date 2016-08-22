#include "DeviceService.h"
#include "DeviceCharacteristic.h"
#include <Packet/ReadPacket.h>

DeviceService :: DeviceService(Service **services, int noServiceInstancePresent)
  : noOfServiceInstancePresent(noServiceInstancePresent + 1) {
  serviceInstanceMap = services;
  serviceInstanceMap[0] = this;

  serviceIdProfileMap = new ServiceIdProfileStruct[noOfServiceInstancePresent];
  serviceCharMap = new Characteristic**[noOfServiceInstancePresent];

  newService(DVC, 0);
}

Characteristic** DeviceService :: construct(int *port){
  Characteristic** chars = new Characteristic*[1];
  chars[0] = new DeviceCharacteristic();
  return chars;
}

unsigned char DeviceService :: newService(ServiceProfile serviceProfileId, int *ports){
    static unsigned char serviceId = 0;

    Service *service = serviceInstanceMap[serviceProfileId];
    serviceCharMap[serviceId] = service->construct(ports);

    serviceIdProfileMap[serviceId].serviceId = serviceId;
    serviceIdProfileMap[serviceId].serviceProfileId = serviceProfileId;

    return serviceId++;
}

void DeviceService :: process(WritePacket *pkt){
  Service :: process(pkt, serviceCharMap[pkt->serviceId], digitalWriteCallback);
}

ResponsePacket* DeviceService :: process(ReadPacket *pkt){
  return Service :: process(pkt, serviceCharMap[pkt->serviceId]);
}

ResponsePacket * DeviceService :: supportedServicesResponsePacket(){
  byte binPkt[] = {
    0x01, 0x03, 0x01, 0x01, 0x01,
    0x01,  //serviceId
    0x01, 0x01 //charCount, charIds
  };
  return process(ReadPacket::parse(binPkt));
}

void DeviceService :: attachDigitalWriteCallBack(int (* callback)(int, int)){
  digitalWriteCallback = callback;
}

ServiceIdProfileStruct DeviceService :: getServiceIdProfile(int index){
  return serviceIdProfileMap[index];
}
