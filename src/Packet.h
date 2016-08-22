#ifndef PACKET_H
#define PACKET_H

#include "common.h"

typedef struct {
  int id;
  int dataLen;
  byte * data;
} CharStruct;

const int SIZE_OF_CHAR_STRUCT = sizeof(CharStruct);

class Packet {
  public:
    byte serviceId;
    byte charCount;
    void consumeHeader(byte *);
};

#endif
