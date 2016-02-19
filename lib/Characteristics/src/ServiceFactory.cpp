#include "ServiceFactory.h"

Characteristic* ServiceFactory::serviceCharMap[4];

Service *ServiceFactory::serviceInstanceMap[1] = {new SwitchService()};

int ServiceFactory::newService(ServiceProfile serviceProfileId, int *ports){
    static int serviceId = 0;
    Service *service = serviceInstanceMap[serviceProfileId];
    serviceCharMap[serviceId] = service->construct(ports);

    return serviceId;
}
