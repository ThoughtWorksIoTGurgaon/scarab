#include "WritePacket.h"

static const int SERVICE_ID_INDEX = 5;
static const int CHARACTERISTICS_COUNT_INDEX = 6;
static const int CHARACTERISTICS_BUFFER_START_INDEX = 7;
static const int BIN_PACKET_HEADER_BYTE_SIZE = 7;

void WritePacket :: construct(CharStruct *chStructs) {
  charsStruct = chStructs;
}

WritePacket* WritePacket :: parse(byte *binPacket){
  self.consumeHeader(binPacket);

  CharStruct * chStructs = new CharStruct[self.charCount];

  for (int characteristicsIndex = 0; characteristicsIndex < self.charCount; characteristicsIndex++) {
      chStructs[characteristicsIndex].id = binPacket[CHARACTERISTICS_BUFFER_START_INDEX + characteristicsIndex*SIZE_OF_CHAR_STRUCT + 0]-1;
      chStructs[characteristicsIndex].dataLen = binPacket[CHARACTERISTICS_BUFFER_START_INDEX + characteristicsIndex*SIZE_OF_CHAR_STRUCT + 1];
      chStructs[characteristicsIndex].data = new byte[chStructs[characteristicsIndex].dataLen];

      for (int characteristicDataIndex = 0; characteristicDataIndex < chStructs[characteristicsIndex].dataLen; characteristicDataIndex++) {
        chStructs[characteristicsIndex].data[characteristicDataIndex] = binPacket[CHARACTERISTICS_BUFFER_START_INDEX + characteristicsIndex*SIZE_OF_CHAR_STRUCT + 1 + 1 + characteristicDataIndex];
      }
   }

   self.construct(chStructs);

  return &self;
}
