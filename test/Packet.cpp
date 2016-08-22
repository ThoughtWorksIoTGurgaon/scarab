#include "gtest/gtest.h"

#include "Packet.h"

TEST(packet, shouldStringifyResponseHavingZeroCharsData)
{
  ResponsePacket *pkt = &Packet::responsePacket;

  pkt->serviceId = 0;
  pkt->charCount = 0;

  char *responseString = Packet :: stringifyResponse(pkt);
  char expectedResponseString[] = {
    0x01, //Version
    0x04, //ResponsePacketType
    0x01, 0x01, 0x01, //Unused
    0x01,  //serviceId
    0x00, //charsCount
    0x00 //Ending string
  };

  ASSERT_STREQ(responseString, expectedResponseString);
}

TEST(packet, shouldStringifyResponseHavingOneCharsData)
{
  ResponsePacket *pkt = &Packet::responsePacket;

  pkt->serviceId = 3;
  pkt->charCount = 1;
  pkt->charsStruct = new CharStruct[1];
  pkt->charsStruct[0].id = 1;
  pkt->charsStruct[0].dataLen = 1;
  pkt->charsStruct[0].data = new byte[1];
  pkt->charsStruct[0].data[0] = 0x01;

  char *responseString = Packet :: stringifyResponse(pkt);
  char expectedResponseString[] = {
    0x01, //Version
    0x04, //ResponsePacketType
    0x01, 0x01, 0x01, //Unused
    0x04,  //serviceId
    0x01, //charsCount
    0x01, 0x01, 0x01, //firstChar Id, dataLen, data
    0x00 //Ending string
  };

  ASSERT_STREQ(responseString, expectedResponseString);
}
