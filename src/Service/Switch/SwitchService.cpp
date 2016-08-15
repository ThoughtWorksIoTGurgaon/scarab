#include "SwitchService.h"
#include "SwitchCharacteristic.h"

Characteristic** SwitchService::construct(int *port){
    return new Characteristic*[1]{
        new SwitchCharacteristic(port[0])
    };
}
