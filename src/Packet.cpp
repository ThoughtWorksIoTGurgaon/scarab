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

#include "Packet.h"

static const int SERVICE_ID_INDEX = 5;
static const int CHARACTERISTICS_COUNT_INDEX = 6;
static const int CHARACTERISTICS_BUFFER_START_INDEX = 7;
static const int BIN_PACKET_HEADER_BYTE_SIZE = 7;

ResponsePacket Packet :: responsePacket;

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

  int lastWrittenIndex = BIN_PACKET_HEADER_BYTE_SIZE - 1;
  for (int index = 0; index < responsePacket->charCount; index++) {
    binPacket[++lastWrittenIndex] = responsePacket->charsStruct[index].id;
    binPacket[++lastWrittenIndex] = responsePacket->charsStruct[index].dataLen;

    for (int characteristicsDataByteIndex = 0; characteristicsDataByteIndex < responsePacket->charsStruct[index].dataLen; characteristicsDataByteIndex++) {
      binPacket[++lastWrittenIndex] = responsePacket->charsStruct[index].data[characteristicsDataByteIndex];
    }
  }

  binPacket[++lastWrittenIndex] = 0;

  return binPacket;
}

Packet* Packet :: consumeHeader(byte* binPacket) {
  this->serviceId = binPacket[SERVICE_ID_INDEX]-1;
  this->charCount = binPacket[CHARACTERISTICS_COUNT_INDEX];
}
