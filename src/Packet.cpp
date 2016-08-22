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

void Packet :: consumeHeader(byte* binPacket) {
  this->serviceId = binPacket[SERVICE_ID_INDEX]-1;
  this->charCount = binPacket[CHARACTERISTICS_COUNT_INDEX];
}
