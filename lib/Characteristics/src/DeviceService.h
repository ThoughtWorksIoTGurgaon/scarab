#ifndef DEVICE_SERVICE_H
#define DEVICE_SERVICE_H
#include "Service.h"

typedef struct{
  ServiceProfile serviceProfileId;
  char serviceId;
} ServiceIdProfileMap;
class DeviceService : public Service{
  public:
      static ServiceIdProfileMap serviceIdProfileMap[2];
      DeviceService(){}
      Characteristic ** construct(int *port);
};
#endif
