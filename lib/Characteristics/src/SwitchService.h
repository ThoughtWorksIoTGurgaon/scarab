#ifndef SWITCH_SERVICE_H
#define SWITCH_SERVICE_H

#include "Service.h"
class SwitchService : public Service{
public:
  SwitchService(){}
  Characteristic * construct(int *port);
};

#endif
