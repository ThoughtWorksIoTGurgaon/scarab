#ifndef RESPONSEPACKET_H
#define RESPONSEPACKET_H

#include <Packet.h>

class ResponsePacket : public Packet {
  private :
    static ResponsePacket *self;
    ResponsePacket(){}
  public :
    CharStruct *charsStruct;
    static ResponsePacket* construct(byte, byte, CharStruct *);
    byte * toBytes();
};

#endif
