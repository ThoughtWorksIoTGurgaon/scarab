#ifndef PACKET_H
#define PACKET_H

#include "common.h"

typedef struct {
  int id;
  int dataLen;
  byte * data;
} CharStruct;

typedef struct {
    int serviceId;
    int charCount;
    CharStruct *charsStruct;
} ResponsePacket;

class Packet {
  private:
  protected:
  public:
    static ResponsePacket responsePacket;
    byte serviceId;
    byte charCount;
    Packet* consumeHeader(byte *);
    static char* stringifyResponse(ResponsePacket *);
    static const int SIZE_OF_CHAR_STRUCT = sizeof(CharStruct);
};

#endif
