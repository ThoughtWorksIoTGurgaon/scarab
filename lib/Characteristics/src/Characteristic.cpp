#include "Arduino.h"
#include "Characteristic.h"

Characteristic::Characteristic(int portNumber){
  this->portNumber=portNumber;
}
void Characteristic::write(int dataLen, char *data, int (* digitalWriteCallback)(int, int)) {
Serial.println("data");
Serial.println(data[0] == ON);

    if(data[0] == ON) {
      if(HIGH == digitalWriteCallback(portNumber, HIGH)){
          status = "H";
          // Serial.println("pqr");
      }
      // Serial.println("asd");
    }
    else if(data[0] == OFF) {
      if(LOW == digitalWriteCallback(portNumber, LOW)){
          status = "L";
      }
    }

    Serial.println("status");
    Serial.println(status);
  }
