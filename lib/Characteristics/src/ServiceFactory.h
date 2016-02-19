#ifndef SERVICE_FACTORY_H
#define SERVICE_FACTORY_H

#include "Service.h"
#include "SwitchService.h"
#include "DeviceService.h"

typedef enum {
  DVC, SWH
} ServiceProfile;

class ServiceFactory{
  public:
    static Service *(serviceInstanceMap[2]);
    static Characteristic** serviceCharMap[2];
    static int newService(ServiceProfile serviceProfileId, int *ports);
};
#endif
