#include "ResponsePacket.h"

static const int BIN_PACKET_HEADER_BYTE_SIZE = 7;

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
  byte *binPacket = new byte[BIN_PACKET_HEADER_BYTE_SIZE + this->charCount*2 + allCharDataLen + 1];

  binPacket[0] = 0x01; //Version
  binPacket[1] = 0x04; //ResponsePacketType
  binPacket[2] = 0x01; //Unused Header Byte
  binPacket[3] = 0x01; //Unused Header Byte
  binPacket[4] = 0x01; //Unused Header Byte
  binPacket[5] = this->serviceId + 1;
  binPacket[6] = this->charCount;

  int lastWrittenIndex = BIN_PACKET_HEADER_BYTE_SIZE - 1;
  for (int index = 0; index < this->charCount; index++) {
    binPacket[++lastWrittenIndex] = this->charsStruct[index].id;
    binPacket[++lastWrittenIndex] = this->charsStruct[index].dataLen;

    for (int characteristicsDataByteIndex = 0; characteristicsDataByteIndex < this->charsStruct[index].dataLen; characteristicsDataByteIndex++) {
      binPacket[++lastWrittenIndex] = this->charsStruct[index].data[characteristicsDataByteIndex];
    }
  }

  binPacket[++lastWrittenIndex] = 0;

  return binPacket;
}

void ResponsePacket :: destroy() {
  delete this->charsStruct;
}
