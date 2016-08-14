#include "ServiceFactory.h"
#define NO_OF_SUPPORTED_SERVICES 2
#define NO_OF_SERVICES_INSTANTIATED 2

Characteristic** ServiceFactory::serviceCharMap[NO_OF_SERVICES_INSTANTIATED];

Service *ServiceFactory::serviceInstanceMap[NO_OF_SUPPORTED_SERVICES] = {
  new DeviceService(),
  new SwitchService()
};

int ServiceFactory::newService(ServiceProfile serviceProfileId, int *ports){
    static int serviceId = 0;
    Service *service = serviceInstanceMap[serviceProfileId];
    serviceCharMap[serviceId] = service->construct(ports);
    DeviceService :: serviceIdProfileMap[serviceId]={serviceProfileId, serviceId};
    return serviceId++;
}
