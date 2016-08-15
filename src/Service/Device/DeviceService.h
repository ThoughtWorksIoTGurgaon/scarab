#ifndef DEVICE_SERVICE_H
#define DEVICE_SERVICE_H
#include <Service.h>
#include <Packet.h>
#define DVC_SERVICE_ID 0
#define DVC_CHAR_ID 0

typedef struct{
  ServiceProfile serviceProfileId;
  unsigned char serviceId;
} ServiceIdProfileMap;

class DeviceService : public Service{
  private:
    Service **serviceInstanceMap;
    Characteristic*** serviceCharMap;
    int (* digitalWriteCallback)(int, int);

  public:
      ServiceIdProfileMap *serviceIdProfileMap;
      const int noOfServiceInstancePresent;

      DeviceService(Service **services, int noServiceInstancePresent);
      void attachDigitalWriteCallBack(int (* callback)(int, int));
      ResponsePacket * supportedServicesResponsePacket();
      Characteristic ** construct(int *port);
      unsigned char newService(ServiceProfile serviceProfileId, int *ports);
      void process(WritePacket *pkt);
      ResponsePacket* process(ReadPacket *pkt);
};

extern DeviceService deviceService;

#endif
