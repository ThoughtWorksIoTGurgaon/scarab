#ifndef SERVICE_H
#define SERVICE_H

#include "Characteristic.h"
#include "Packet/ReadPacket.h"
#include "Packet/WritePacket.h"
#include "Packet/ResponsePacket.h"

typedef enum {
  DVC, SWH
} ServiceProfile;

class Service{
  public:
      virtual Characteristic ** construct(int *port)=0;
      static void consume(WritePacket *pkt, Characteristic** allChars, int (* digitalWriteCallback)(int, int));
      static  ResponsePacket * consume(ReadPacket *pkt, Characteristic** allChars);
};

#endif
