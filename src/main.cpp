#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ELClient.h>
#include <ELClientMqtt.h>

#include <Service/Device/DeviceService.h>
#include <Service/Switch/SwitchService.h>

#define NO_OF_SUPPORTED_SERVICES 2
#define NO_OF_SERVICES_INSTANTIATED 2

SoftwareSerial softwareSerial(2, 3); // RX, TX

// Initialize a connection to esp-link using the normal hardware serial port both for
// SLIP and for debug messages.
ELClient esp(&Serial, &Serial);
// Initialize the MQTT client
ELClientMqtt mqtt(&esp);

DeviceService deviceService(
  new Service*[NO_OF_SUPPORTED_SERVICES]{0, new SwitchService()},
  NO_OF_SERVICES_INSTANTIATED
);

void wifiCb(void* response) {
  Serial.println("Wifi Connected");
}

void mqttConnected(void* response)
{
  Serial.println("Connected");
  mqtt.subscribe("/device/my-device-id/cmd");

  char binPkt[] = {
    0x01, 0x03, 0x01, 0x01, 0x01,
    0x01,  //serviceId
    0x01, 0x01 //charCount, charIds
  };

  ReadPacket* readPacket = Packet::parseRead(binPkt);
  ResponsePacket *responsePacket = deviceService.process(readPacket);
  mqtt.publish("/device/my-device-id/data", Packet :: stringifyResponse(responsePacket));
}
void mqttDisconnected(void* response){}

void mqttData(void* response)
{
  ELClientResponse *res = (ELClientResponse *)response;

  String topic = res->popString();
  String data = res->popString();

  deviceService.process(Packet::parseWrite(data.c_str()));
}

void mqttPublished(void* response){}

int digitalWriteCallback(int portNumber, int level){
  digitalWrite(portNumber, level);
  return level;
}

void setup() {
  Serial.begin(115200);
  softwareSerial.begin(115200);

  // Sync-up with esp-link, this is required at the start of any sketch and initializes the
  // callbacks to the wifi status change callback. The callback gets called with the initial
  // status right after Sync() below completes.
  esp.wifiCb.attach(wifiCb); // wifi status change callback, optional (delete if not desired)
  bool ok = false;
  while(!(ok = esp.Sync())) {// sync up with esp-link, blocks for up to 2 seconds
    Serial.println("EL-Client sync failed!");
  }

  Serial.println("EL-Client synced!");

  // Set-up callbacks for events and initialize with es-link.
  mqtt.connectedCb.attach(mqttConnected);
  mqtt.disconnectedCb.attach(mqttDisconnected);
  mqtt.publishedCb.attach(mqttPublished);
  mqtt.dataCb.attach(mqttData);
  mqtt.setup();

  Serial.println("EL-MQTT ready");

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  deviceService.attachDigitalWriteCallBack(digitalWriteCallback);
  deviceService.newService(SWH, new int[1]{13});
}

void loop() {
  esp.Process();
}
