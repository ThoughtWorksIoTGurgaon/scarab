#include <Characteristic.h>

class DeviceCharacteristic : public Characteristic{
  public:
    DeviceCharacteristic():Characteristic(0){}
    void write(int, char *, int (* digitalWriteCallback)(int, int));
    char* read();
};
