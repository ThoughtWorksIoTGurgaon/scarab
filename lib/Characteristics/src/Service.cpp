#include "Arduino.h"
#include "Service.h"
#include "Packet.h"
#include "ServiceFactory.h"

int digitalWriteCallback(int portNumber, int level){
  digitalWrite(portNumber, level);
  return level;
}

void Service :: process(WritePacket *pkt){
      Characteristic** allChars = ServiceFactory::serviceCharMap[pkt->serviceId];

      int charCount = pkt->charCount;

      for (int i = 0; i < charCount; i++) {
        CharStruct charStruct = pkt->charsStruct[i];

        Characteristic *ch = allChars[charStruct.id];

        ch->write(charStruct.dataLen, charStruct.data, &digitalWriteCallback);
      }
}
 ResponsePacket* Service :: process(ReadPacket *pkt){
   Characteristic** allChars = ServiceFactory::serviceCharMap[pkt->serviceId];
   Packet :: responsePacket.serviceId = pkt -> serviceId;
   int charCount = pkt->charCount;
   Packet :: responsePacket.charCount = charCount;
   const char *charIds = pkt->characteristicIds;
   Packet :: responsePacket.charsStruct = new CharStruct[charCount];
   for (int i = 0; i < charCount; i++) {
     Characteristic *ch = allChars[charIds[i]-1];
     char *data = ch->read();
     CharStruct charStruct = {charIds[i], data[0], data+1};
     Packet :: responsePacket.charsStruct[i] = charStruct;
   }
   return &Packet :: responsePacket;
 }
