/*

  ____   ____    _    ____      _    ____
 / ___| / ___|  / \  |  _ \    / \  | __ )
 \___ \| |     / _ \ | |_) |  / _ \ |  _ \
  ___) | |___ / ___ \|  _ <  / ___ \| |_) |
 |____/ \____/_/   \_\_| \_\/_/   \_\____/


PACKET.CPP

Packet format for scarab
_______________________________________________________________________________________________
|Version|UNUSED|UNUSED|UNUSED|PACKET_TYPE|SERVICE_ID|CHARACTERISTICS_COUNT|CHARACTERISTICS....|
-----------------------------------------------------------------------------------------------

CHARACTERISTIC PACKET FORMAT
__________________________________________________________________
|CHARACTERISTIC_ID|CHARACTERISTIC_DATA_LENGTH|CHARACTERISTIC_DATA|
------------------------------------------------------------------

*/

#include <string.h>
#include "Packet.h"

static const int SERVICE_ID_INDEX = 5;
static const int CHARACTERISTICS_COUNT_INDEX = 6;
static const int CHARACTERISTICS_BUFFER_START_INDEX = 7;
static const int BIN_PACKET_HEADER_BYTE_SIZE = 7;

WritePacket Packet :: writePacket;
ReadPacket Packet :: readPacket;
ResponsePacket Packet :: responsePacket;

WritePacket* Packet :: parseWrite(const char *binPacket) {
  writePacket.serviceId = binPacket[SERVICE_ID_INDEX]-1;
  writePacket.charCount = binPacket[CHARACTERISTICS_COUNT_INDEX];
  writePacket.charsStruct = new CharStruct[writePacket.charCount];

  for (int characteristicsIndex = 0; characteristicsIndex < writePacket.charCount; characteristicsIndex++) {
      writePacket.charsStruct[characteristicsIndex].id = binPacket[CHARACTERISTICS_BUFFER_START_INDEX + characteristicsIndex*SIZE_OF_CHAR_STRUCT + 0]-1;
      writePacket.charsStruct[characteristicsIndex].dataLen = binPacket[CHARACTERISTICS_BUFFER_START_INDEX + characteristicsIndex*SIZE_OF_CHAR_STRUCT + 1];
      writePacket.charsStruct[characteristicsIndex].data = new char[writePacket.charsStruct[characteristicsIndex].dataLen];

      for (int characteristicDataIndex = 0; characteristicDataIndex < writePacket.charsStruct[characteristicsIndex].dataLen; characteristicDataIndex++) {
        writePacket.charsStruct[characteristicsIndex].data[characteristicDataIndex] = binPacket[CHARACTERISTICS_BUFFER_START_INDEX + characteristicsIndex*SIZE_OF_CHAR_STRUCT + 1 + 1 + characteristicDataIndex];
      }
   }

   return &writePacket;
 }

ReadPacket* Packet :: parseRead(const char *binPacket){
  readPacket.serviceId = binPacket[SERVICE_ID_INDEX]-1;
  readPacket.charCount = binPacket[CHARACTERISTICS_COUNT_INDEX];
  readPacket.characteristicIds = &binPacket[CHARACTERISTICS_BUFFER_START_INDEX];

  return &readPacket;
}


char* Packet :: stringifyResponse(ResponsePacket *responsePacket){
  int allCharDataLen = 0;
  for (int i = 0; i < responsePacket->charCount; i++) {
    allCharDataLen += responsePacket->charsStruct[i].dataLen;
  }
  char *binPacket = new char[BIN_PACKET_HEADER_BYTE_SIZE + responsePacket->charCount*2 + allCharDataLen + 1];

  binPacket[0] = 0x01; //Version
  binPacket[1] = 0x04; //ResponsePacketType
  binPacket[2] = 0x01; //Unused Header Byte
  binPacket[3] = 0x01; //Unused Header Byte
  binPacket[4] = 0x01; //Unused Header Byte
  binPacket[5] = responsePacket->serviceId + 1; 
  binPacket[6] = responsePacket->charCount; 

  int characteristicsStartIndex = BIN_PACKET_HEADER_BYTE_SIZE - 1;
  for (int index = 0; index < responsePacket->charCount; index++) {
    binPacket[++characteristicsStartIndex] = responsePacket->charsStruct[index].id;
    binPacket[++characteristicsStartIndex] = responsePacket->charsStruct[index].dataLen;

    for (int characteristicsDataByteIndex = 0; characteristicsDataByteIndex < responsePacket->charsStruct[characteristicsStartIndex].dataLen; characteristicsDataByteIndex++) {
      binPacket[++characteristicsStartIndex] = responsePacket->charsStruct[characteristicsStartIndex].data[characteristicsDataByteIndex];
    }
  }

  binPacket[++characteristicsStartIndex] = 0;

  return binPacket;
}
