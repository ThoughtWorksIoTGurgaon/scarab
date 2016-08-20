#include "gtest/gtest.h"
#include "Packet.h"

TEST(packet, shouldReadPacketForOneServiceAndOnceCharacteristic)
{
  char binPkt[] = {
    0x01, 0x03, 0x01, 0x01, 0x01, //header
    0x01,  //serviceId
    0x01, 0x01 //charCount, charIds
  };

  ReadPacket* readPacket = Packet :: parseRead(binPkt);
  ASSERT_EQ(readPacket->serviceId, 0);
  ASSERT_EQ(readPacket->charCount, 1);

  char characteristicIds[] = {0x01};

  for (size_t i = 0; i < readPacket->charCount; ++i) {
    ASSERT_EQ(readPacket->characteristicIds[i], characteristicIds[i]);
  }
}

TEST(packet, shouldReadPacketForOneServiceAndTwoCharacteristic)
{
  char binPkt[] = {
    0x01, 0x03, 0x01, 0x01, 0x01, //header
    0x04,  //serviceId
    0x02, 0x02, 0x01 //charCount, charIds...
  };

  ReadPacket* readPacket = Packet :: parseRead(binPkt);
  ASSERT_EQ(readPacket->serviceId, 3);
  ASSERT_EQ(readPacket->charCount, 2);

  char characteristicIds[] = {0x02, 0x01};

  for (size_t i = 0; i < readPacket->charCount; ++i) {
    ASSERT_EQ(readPacket->characteristicIds[i], characteristicIds[i]);
  }
}
