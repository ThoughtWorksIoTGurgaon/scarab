#include "Service.h"
// #include <iostream>

// using namespace std;

void Service :: consume(WritePacket *pkt, Characteristic** allChars, int (* digitalWriteCallback)(int, int)){
  byte charCount = pkt->charCount;

  for (byte i = 0; i < charCount; i++) {
    CharStruct charStruct = pkt->charsStruct[i];

    Characteristic *ch = allChars[charStruct.id];

    ch->write(charStruct.dataLen, charStruct.data, digitalWriteCallback);
  }

  pkt->destroy();
}

ResponsePacket* Service :: consume(ReadPacket *pkt, Characteristic** allChars){
   byte serviceId = pkt -> serviceId;
   byte charCount = pkt -> charCount;

  // cerr<<"Count of characteristics: "<<charCount<<endl;
  // cerr<<"ServiceID"<<serviceId;
   byte *charIds = pkt->characteristicIds;
   CharStruct *charsStruct = new CharStruct[charCount];

   for (int i = 0; i < charCount; i++) {
    //  std::cerr << "Loop: " << i << '\n';
     Characteristic *ch = allChars[charIds[i] - 1];
    //  std::cerr<< "Before read";
     byte *data = ch->read();
     CharStruct charStruct = {charIds[i], data[0], data+1};
     charsStruct[i] = charStruct;
   }

   pkt->destroy();

   return ResponsePacket::construct(
       serviceId,
       charCount,
       charsStruct
     );
 }
