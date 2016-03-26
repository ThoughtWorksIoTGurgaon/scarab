#ifndef SERVICE_H
#define SERVICE_H

#include "Arduino.h"
#include "Characteristic.h"
#include "Packet.h"

typedef enum {
  DVC, SWH
} ServiceProfile;

class Service{
  public:
      virtual Characteristic ** construct(int *port)=0;
      static void process(WritePacket *pkt);
      static  ResponsePacket * process(ReadPacket *pkt);
};


#endif
