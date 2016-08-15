#include "Service.h"
#include "Packet.h"


void Service :: process(WritePacket *pkt, Characteristic** allChars, int (* digitalWriteCallback)(int, int)){
      int charCount = pkt->charCount;

      for (int i = 0; i < charCount; i++) {
        CharStruct charStruct = pkt->charsStruct[i];

        Characteristic *ch = allChars[charStruct.id];

        ch->write(charStruct.dataLen, charStruct.data, digitalWriteCallback);
      }
}
 ResponsePacket* Service :: process(ReadPacket *pkt, Characteristic** allChars){
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
