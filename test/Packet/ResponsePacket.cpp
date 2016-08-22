#include "gtest/gtest.h"

#include <Packet/ResponsePacket.h>

TEST(packet, shouldStringifyResponseHavingZeroCharsData)
{
  char expectedResponseString[] = {
    0x01, //Version
    0x04, //ResponsePacketType
    0x01, 0x01, 0x01, //Unused
    0x01,  //serviceId
    0x00, //charsCount
    0x00 //Ending string
  };

  ResponsePacket *pkt = ResponsePacket::construct(0, 0, 0);

  ASSERT_STREQ((char *)pkt->toBytes(), expectedResponseString);
}

TEST(packet, shouldStringifyResponseHavingOneCharsData)
{
  CharStruct *charsStruct = new CharStruct[1];
  charsStruct[0].id = 1;
  charsStruct[0].dataLen = 1;
  charsStruct[0].data = new byte[1];
  charsStruct[0].data[0] = 0x01;

  ResponsePacket *pkt = ResponsePacket::construct(
    3, //serviceId
    1, //charsCount
    charsStruct
  );

  char expectedResponseString[] = {
    0x01, //Version
    0x04, //ResponsePacketType
    0x01, 0x01, 0x01, //Unused
    0x04,  //serviceId
    0x01, //charsCount
    0x01, 0x01, 0x01, //firstChar Id, dataLen, data
    0x00 //Ending string
  };

  ASSERT_STREQ((char *)pkt->toBytes(), expectedResponseString);
}
