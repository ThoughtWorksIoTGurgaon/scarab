#include <Characteristic.h>

class DeviceCharacteristic : public Characteristic{
  public:
    DeviceCharacteristic():Characteristic(0){}
    void write(int, byte *, int (* digitalWriteCallback)(int, int));
    byte* read();
};
