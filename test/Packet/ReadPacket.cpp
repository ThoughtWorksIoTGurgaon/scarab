#include "gtest/gtest.h"

#include <Packet/ReadPacket.h>

TEST(packet, shouldReadPacketForOneServiceAndZeroCharacteristic)
{
  byte binPkt[] = {
    0x01, 0x03, 0x01, 0x01, 0x01, //header
    0x01,  //serviceId
    0x00  //charCount
  };

  ReadPacket* readPacket = ReadPacket :: parse(binPkt);
  ASSERT_EQ(readPacket->serviceId, 0);
  ASSERT_EQ(readPacket->charCount, 0);
}

TEST(packet, shouldReadPacketForOneServiceAndOneCharacteristic)
{
  byte binPkt[] = {
    0x01, 0x03, 0x01, 0x01, 0x01, //header
    0x01,  //serviceId
    0x01, 0x01 //charCount, charIds
  };

  ReadPacket* readPacket = ReadPacket :: parse(binPkt);
  ASSERT_EQ(readPacket->serviceId, 0);
  ASSERT_EQ(readPacket->charCount, 1);

  byte characteristicIds[] = {0x01};

  for (size_t i = 0; i < readPacket->charCount; ++i) {
    ASSERT_EQ(readPacket->characteristicIds[i], characteristicIds[i]);
  }
}

TEST(packet, shouldReadPacketForOneServiceAndTwoCharacteristic)
{
  byte binPkt[] = {
    0x01, 0x03, 0x01, 0x01, 0x01, //header
    0x04,  //serviceId
    0x02, 0x02, 0x01 //charCount, charIds...
  };

  ReadPacket* readPacket = ReadPacket :: parse(binPkt);
  ASSERT_EQ(readPacket->serviceId, 3);
  ASSERT_EQ(readPacket->charCount, 2);

  byte characteristicIds[] = {0x02, 0x01};

  for (size_t i = 0; i < readPacket->charCount; ++i) {
    ASSERT_EQ(readPacket->characteristicIds[i], characteristicIds[i]);
  }
}

TEST(packet, shouldReadPacketAndReturnWithoutConsumingAnyMemory)
{
  byte binPkt1[] = {
    0x01, 0x03, 0x01, 0x01, 0x01, //header
    0x01,  //serviceId
    0x00  //charCount
  };

  ReadPacket* readPacket1 = ReadPacket :: parse(binPkt1);

  byte binPkt2[] = {
    0x01, 0x03, 0x01, 0x01, 0x01, //header
    0x04,  //serviceId
    0x02, 0x02, 0x01 //charCount, charIds...
  };

  ReadPacket* readPacket2 = ReadPacket :: parse(binPkt2);

  //both readPackets are pointing to same memory address
  ASSERT_EQ(readPacket1, readPacket2);
}
