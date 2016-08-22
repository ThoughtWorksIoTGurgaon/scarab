#include "ReadPacket.h"

static const int SERVICE_ID_INDEX = 5;
static const int CHARACTERISTICS_COUNT_INDEX = 6;
static const int CHARACTERISTICS_BUFFER_START_INDEX = 7;
static const int BIN_PACKET_HEADER_BYTE_SIZE = 7;

ReadPacket* ReadPacket::self = new ReadPacket;

void ReadPacket :: construct(byte *charsIds) {
  characteristicIds = charsIds;
}

ReadPacket* ReadPacket :: parse(byte *binPacket){
  self->consumeHeader(binPacket);

  self->construct(
    &binPacket[CHARACTERISTICS_BUFFER_START_INDEX]
  );

  return self;
}
