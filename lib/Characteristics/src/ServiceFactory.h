#ifndef SERVICE_FACTORY_H
#define SERVICE_FACTORY_H

#include "Service.h"
#include "SwitchService.h"

typedef enum {
  SWH
} ServiceProfile;

class ServiceFactory{
  public:
    static Service *(serviceInstanceMap[1]);
    static Characteristic* serviceCharMap[4];
    static int newService(ServiceProfile serviceProfileId, int *ports);
};
#endif
