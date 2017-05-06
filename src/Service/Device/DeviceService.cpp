#include "DeviceService.h"
#include "DeviceCharacteristic.h"
#include <Packet/ReadPacket.h>
// #include <stdio.h>
// #include <iostream>
// #include <iomanip>
// using namespace std;

#define DEVICE_SERVICE_ID 0
#define DEVICE_DISCOVERY_CHAR_ID 0

DeviceService :: DeviceService(Service **services, int noServiceInstancePresent)
  : noOfServiceInstancePresent(noServiceInstancePresent + 1) {
  serviceInstanceMap = services;
  serviceInstanceMap[0] = this;

  serviceIdProfileMap = new ServiceIdProfileStruct[noOfServiceInstancePresent];
  serviceCharMap = new Characteristic**[noOfServiceInstancePresent];

  // printf("Building device service");
  // printf("No of services present: %d", this->noOfServiceInstancePresent);
  // printf("Now Constructing device discovery service");
  newService(DVC, DEVICE_SERVICE_ID);
}

Characteristic** DeviceService :: construct(int *port){
  Characteristic** chars = new Characteristic*[1];
  chars[DEVICE_DISCOVERY_CHAR_ID] = new DeviceCharacteristic();
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

void DeviceService :: consume(WritePacket *pkt){
  Service :: consume(pkt, serviceCharMap[pkt->serviceId], digitalWriteCallback);
}

ResponsePacket* DeviceService :: consume(ReadPacket *pkt){
  return Service :: consume(pkt, serviceCharMap[pkt->serviceId]);
}

ResponsePacket * DeviceService :: supportedServicesResponsePacket(){
  // cerr<<"Building supportedServicesResponsePacket";
  byte charCount = 1;
  byte *charIds = new byte[charCount];
  charIds[0] = DEVICE_DISCOVERY_CHAR_ID;

  // cerr<<"Char count from outside is" << std::hex << std::setw(2)<< std::setfill('0') << static_cast<unsigned int>(charCount) <<endl;
  //0, 1, 0
  return consume(ReadPacket::construct(
    DEVICE_SERVICE_ID, charCount, charIds //serviceId, charCount, charIds
  ));
}

void DeviceService :: attachDigitalWriteCallBack(int (* callback)(int, int)){
  digitalWriteCallback = callback;
}

ServiceIdProfileStruct DeviceService :: getServiceIdProfile(int index){
  return serviceIdProfileMap[index];
}
