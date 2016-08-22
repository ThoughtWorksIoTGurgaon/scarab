#ifndef WRITEPACKET_H
#define WRITEPACKET_H

#include <Packet.h>

class WritePacket : public Packet {
  private :
    static WritePacket self;
    WritePacket(){}
  public :
    CharStruct *charsStruct;
    void construct(CharStruct *);
    static WritePacket* parse(byte*);
};

#endif
