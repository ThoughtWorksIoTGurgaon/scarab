#include "SwitchService.h"

Characteristic* SwitchService::construct(int *port){
    return new Characteristic[1]{
      Characteristic(port[0])
    };
}
