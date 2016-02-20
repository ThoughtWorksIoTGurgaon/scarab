#ifndef PACKET_H
#define PACKET_H


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
  const char *characteristicIds;
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
    static ReadPacket* parseRead(const char *) ;
    static char* stringifyResponse(ResponsePacket *);
};

#endif
