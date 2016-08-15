#include "DeviceService.h"
#include "DeviceCharacteristic.h"

Characteristic** DeviceService :: construct(int *port){
  return new Characteristic*[1]{
      new DeviceCharacteristic()
  };
}

unsigned char DeviceService :: newService(ServiceProfile serviceProfileId, int *ports){
    static unsigned char serviceId = 0;
    Service *service = serviceInstanceMap[serviceProfileId];
    serviceCharMap[serviceId] = service->construct(ports);
    serviceIdProfileMap[serviceId]={serviceProfileId, serviceId};
    return serviceId++;
}

void DeviceService :: process(WritePacket *pkt){
  Service :: process(pkt, serviceCharMap[pkt->serviceId], digitalWriteCallback);
}

ResponsePacket* DeviceService :: process(ReadPacket *pkt){
  return Service :: process(pkt, serviceCharMap[pkt->serviceId]);
}
