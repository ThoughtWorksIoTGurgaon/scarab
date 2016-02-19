#ifndef DEVICE_SERVICE_H
#define DEVICE_SERVICE_H
#include "Service.h"
class DeviceService : public Service{
  public:
      DeviceService(){}
      Characteristic ** construct(int *port);
};
#endif
