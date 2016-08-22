#ifndef SERVICE_H
#define SERVICE_H

#include "Characteristic.h"
#include "Packet/ReadPacket.h"
#include "Packet/WritePacket.h"

typedef enum {
  DVC, SWH
} ServiceProfile;

class Service{
  public:
      virtual Characteristic ** construct(int *port)=0;
      static void process(WritePacket *pkt, Characteristic** allChars, int (* digitalWriteCallback)(int, int));
      static  ResponsePacket * process(ReadPacket *pkt, Characteristic** allChars);
};

#endif
