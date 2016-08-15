#ifndef DEVICE_SERVICE_H
#define DEVICE_SERVICE_H
#include <Service.h>

typedef struct{
  ServiceProfile serviceProfileId;
  unsigned char serviceId;
} ServiceIdProfileMap;
class DeviceService : public Service{
  public:
      Service **serviceInstanceMap;
      ServiceIdProfileMap *serviceIdProfileMap;
      Characteristic*** serviceCharMap;
      const int noOfServiceInstancePresent;

      int (* digitalWriteCallback)(int, int);

      DeviceService(Service **services, int noServiceInstancePresent)
        : noOfServiceInstancePresent(noServiceInstancePresent + 1) {
        serviceInstanceMap = services;
        serviceInstanceMap[0] = this;

        serviceIdProfileMap = new ServiceIdProfileMap[noOfServiceInstancePresent];
        serviceCharMap = new Characteristic**[noOfServiceInstancePresent];

        newService(DVC, 0);
      }

      void attachDigitalWriteCallBack(int (* callback)(int, int)){
        digitalWriteCallback = callback;
      }

      Characteristic ** construct(int *port);
      unsigned char newService(ServiceProfile serviceProfileId, int *ports);
      void process(WritePacket *pkt);
      ResponsePacket* process(ReadPacket *pkt);
};

extern DeviceService deviceService;

#endif
