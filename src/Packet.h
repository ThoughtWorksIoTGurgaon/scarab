#ifndef PACKET_H
#define PACKET_H

#include "common.h"

typedef struct {
  int id;
  int dataLen;
  char * data;
} CharStruct;

typedef struct {
    int serviceId;
    int charCount;
    CharStruct *charsStruct;
} WritePacket, ResponsePacket;

typedef struct {
  int serviceId;
  int charCount;
  byte *characteristicIds;
} ReadPacket;

class Packet {
  private:
    static WritePacket writePacket;
    static ReadPacket readPacket;
    static const int SIZE_OF_CHAR_STRUCT = sizeof(CharStruct);

  public:
    Packet();
    static ResponsePacket responsePacket;
    static WritePacket* parseWrite(const char *) ;
    static ReadPacket* parseRead(byte *) ;
    static char* stringifyResponse(ResponsePacket *);
};

#endif
