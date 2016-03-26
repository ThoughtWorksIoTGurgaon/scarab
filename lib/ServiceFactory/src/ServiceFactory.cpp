#include "ServiceFactory.h"

Characteristic** ServiceFactory::serviceCharMap[2];

Service *ServiceFactory::serviceInstanceMap[2] = {new DeviceService(), new SwitchService()};

int ServiceFactory::newService(ServiceProfile serviceProfileId, int *ports){
    static int serviceId = 0;
    Service *service = serviceInstanceMap[serviceProfileId];
    serviceCharMap[serviceId] = service->construct(ports);
    DeviceService :: serviceIdProfileMap[serviceId]={serviceProfileId, serviceId};
    return serviceId++;
}
