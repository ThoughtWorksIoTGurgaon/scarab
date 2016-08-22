#include "ReadPacket.h"

static const int SERVICE_ID_INDEX = 5;
static const int CHARACTERISTICS_COUNT_INDEX = 6;
static const int CHARACTERISTICS_BUFFER_START_INDEX = 7;
static const int BIN_PACKET_HEADER_BYTE_SIZE = 7;

ReadPacket* ReadPacket::self = new ReadPacket;

ReadPacket* ReadPacket :: construct(byte serviceId, byte charCount, byte *charsIds) {
  self->serviceId = serviceId;
  self->charCount = charCount;
  self->construct(charsIds);

  return self;
}

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

void ReadPacket :: destroy() {
  delete this->characteristicIds;
}
