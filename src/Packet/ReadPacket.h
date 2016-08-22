#ifndef READPACKET_H
#define READPACKET_H

#include <Packet.h>

class ReadPacket : public Packet {
  private :
    static ReadPacket *self;
  public :
    byte *characteristicIds;
    void construct(byte *charsIds);
    static ReadPacket* parse(byte* pkt);
    void destroy();
};
#endif
