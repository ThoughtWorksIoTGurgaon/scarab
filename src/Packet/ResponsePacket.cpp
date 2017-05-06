#include "ResponsePacket.h"
// #include <stdio.h>

static const int BIN_PACKET_HEADER_BYTE_SIZE = 7;
static const int VERSION_HEADER_BYTE = 0;
static const int ResponsePacketType_HEADER_BYTE = 1;
static const int UNUSED_HEADER_BYTE1 = 2;
static const int UNUSED_HEADER_BYTE2 = 3;
static const int UNUSED_HEADER_BYTE3 = 4;
static const int NO_OF_SERVICES_BYTE = 5;
static const int NO_OF_CHARACTERSTICS = 6;


ResponsePacket* ResponsePacket::self = new ResponsePacket;

ResponsePacket* ResponsePacket :: construct(byte sId, byte chCount, CharStruct *chStructs) {
  self->serviceId = sId;
  self->charCount = chCount;
  self->charsStruct = chStructs;

  return self;
}

byte* ResponsePacket :: toBytes(){
  int allCharDataLen = 0;
  for (int i = 0; i < this->charCount; i++) {
    allCharDataLen += this->charsStruct[i].dataLen;
  }
  // printf("All charDatalen: %d", allCharDataLen);

  int approxSizeOfBinPacket = BIN_PACKET_HEADER_BYTE_SIZE + this->charCount*2 + allCharDataLen + 1;

  byte *binPacket = new byte[approxSizeOfBinPacket];

  binPacket[VERSION_HEADER_BYTE] = 0x01; //Version
  binPacket[ResponsePacketType_HEADER_BYTE] = 0x04; //ResponsePacketType
  binPacket[UNUSED_HEADER_BYTE1] = 0x01; //Unused Header Byte
  binPacket[UNUSED_HEADER_BYTE2] = 0x01; //Unused Header Byte
  binPacket[UNUSED_HEADER_BYTE3] = 0x01; //Unused Header Byte
  binPacket[NO_OF_SERVICES_BYTE] = this->serviceId + 1;
  binPacket[NO_OF_CHARACTERSTICS] = this->charCount;

  // printf("NO OF SERVICES SUPPORTED BY THIS DEVICE: %d", this->serviceId + 1);
  // printf("NO OF CHARACTERISTICS ON THIS DEVICE: %d", this->charCount);

  int lastWrittenIndex = BIN_PACKET_HEADER_BYTE_SIZE - 1;
  for (int characteristicPacketIndex = 0; characteristicPacketIndex < this->charCount; characteristicPacketIndex++) {
    binPacket[++lastWrittenIndex] = this->charsStruct[characteristicPacketIndex].id;
    binPacket[++lastWrittenIndex] = this->charsStruct[characteristicPacketIndex].dataLen;

    for (int characteristicsDataByteIndex = 0; characteristicsDataByteIndex < this->charsStruct[characteristicPacketIndex].dataLen; characteristicsDataByteIndex++) {
      binPacket[++lastWrittenIndex] = this->charsStruct[characteristicPacketIndex].data[characteristicsDataByteIndex];
    }
  }

  binPacket[++lastWrittenIndex] = 0;

  return binPacket;
}

void ResponsePacket :: destroy() {
  delete this->charsStruct;
}
