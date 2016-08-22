#ifndef DEVICE_SERVICE_H
#define DEVICE_SERVICE_H
#include <Service.h>
#include <Packet.h>
#define DVC_SERVICE_ID 0
#define DVC_CHAR_ID 0

typedef struct{
  ServiceProfile serviceProfileId;
  unsigned char serviceId;
} ServiceIdProfileStruct;

class DeviceService : public Service{
  private:
    Service **serviceInstanceMap;
    Characteristic*** serviceCharMap;
    ServiceIdProfileStruct *serviceIdProfileMap;

    int (* digitalWriteCallback)(int, int);
  public:
      const int noOfServiceInstancePresent;

      DeviceService(Service **services, int noServiceInstancePresent);
      void attachDigitalWriteCallBack(int (* callback)(int, int));
      ResponsePacket * supportedServicesResponsePacket();
      ServiceIdProfileStruct getServiceIdProfile(int index);

      Characteristic ** construct(int *port);
      unsigned char newService(ServiceProfile serviceProfileId, int *ports);

      void consume(WritePacket *pkt);
      ResponsePacket* consume(ReadPacket *pkt);
};

extern DeviceService deviceService;
#endif
