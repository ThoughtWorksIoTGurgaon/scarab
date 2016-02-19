#include "string.h"
#include "Packet.h"

#include "Arduino.h"


WritePacket Packet::writePacket;

WritePacket* Packet :: parse(const char *binPacket) {

  writePacket.serviceId = binPacket[5]-1;
  writePacket.charCount = binPacket[6];
  writePacket.charsStruct = new CharStruct[writePacket.charCount];

  for (int i = 0; i < writePacket.charCount; i++) {
      writePacket.charsStruct[i].id = binPacket[7 + i*SIZE_OF_CHAR_STRUCT + 0]-1;
      writePacket.charsStruct[i].dataLen = binPacket[7 + i*SIZE_OF_CHAR_STRUCT + 1];
      writePacket.charsStruct[i].data = new char[writePacket.charsStruct[i].dataLen];

      int j;
      for (j = 0; j < writePacket.charsStruct[i].dataLen; j++) {
        writePacket.charsStruct[i].data[j] = binPacket[7 + i*SIZE_OF_CHAR_STRUCT + 1 + 1 + j];
      }

      // writePacket.charsStruct[i].data[j] = 0;
      // Serial.println("data_");
      // Serial.println(int(writePacket.charsStruct[i].data[0]));
   }

   return &writePacket;
 }
