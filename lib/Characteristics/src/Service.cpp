#include "Arduino.h"
#include "Service.h"
#include "Packet.h"
#include "ServiceFactory.h"

int digitalWriteCallback(int portNumber, int level){
  digitalWrite(portNumber, level);
  return level;
}

void Service :: process(WritePacket *pkt){
      Characteristic* allChars = ServiceFactory::serviceCharMap[pkt->serviceId];

      int charCount = pkt->charCount;

      Serial.println("charCount:");
      Serial.println(charCount);

      for (int i = 0; i < charCount; i++) {
        CharStruct charStruct = pkt->charsStruct[i];

        Characteristic ch = allChars[charStruct.id];

        Serial.println("for charId:");
        Serial.println(charStruct.id);
        ch.write(charStruct.dataLen, charStruct.data, &digitalWriteCallback);
      }
}
