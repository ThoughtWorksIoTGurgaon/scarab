#ifndef SERVICE_H
#define SERVICE_H

#include "Arduino.h"
#include "Characteristic.h"
#include "Packet.h"
class Service{
  public:
      virtual Characteristic * construct(int *port)=0;
      static void process(WritePacket *pkt);
};


#endif
