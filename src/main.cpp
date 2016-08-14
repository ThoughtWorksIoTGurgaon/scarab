#include "Arduino.h"
#include <SoftwareSerial.h>
#include <ServiceFactory.h>
#include <ELClient.h>
#include <ELClientMqtt.h>

SoftwareSerial softwareSerial(2, 3); // RX, TX

// Initialize a connection to esp-link using the normal hardware serial port both for
// SLIP and for debug messages.
ELClient esp(&Serial, &Serial);

// Initialize the MQTT client
ELClientMqtt mqtt(&esp);

boolean wifiConnected = false;

void wifiCb(void* response)
{
  // uint32_t status;
  // RESPONSE res(response);
  Serial.println("Wifi Connected");
  // if(res.getArgc() == 1) {
  //   res.popArgs((uint8_t*)&status, 4);
  //   if(status == STATION_GOT_IP) {
  //     Serial.println("WIFI CONNECTED");
  //     wifiConnected = true;
  //   } else {
  //     wifiConnected = false;
  //   }
  // }
}

void libPublishCallback(char *topic, char *data){
  mqtt.publish(topic, data);
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

  Serial.println("readPacket->serviceId");
  Serial.println(readPacket->serviceId);
  Serial.println("readPacket->charCount");
  Serial.println(readPacket->charCount);

   ResponsePacket *responsePacket = Service::process(readPacket);

  mqtt.publish("/device/my-device-id/data", Packet :: stringifyResponse(responsePacket));
}
void mqttDisconnected(void* response)
{

}
void mqttData(void* response)
{
  ELClientResponse *res = (ELClientResponse *)response;

  Serial.print("Received: topic=");
  String topic = res->popString();
  Serial.println(topic);

  Serial.print("data=");
  String data = res->popString();

  Service::process(Packet::parseWrite(data.c_str()));

  Serial.println(data);
}
void mqttPublished(void* response)
{

}
void setup() {
  Serial.begin(115200);
  softwareSerial.begin(115200);

  // Sync-up with esp-link, this is required at the start of any sketch and initializes the
  // callbacks to the wifi status change callback. The callback gets called with the initial
  // status right after Sync() below completes.
  esp.wifiCb.attach(wifiCb); // wifi status change callback, optional (delete if not desired)
  bool ok;
  do {
    ok = esp.Sync();      // sync up with esp-link, blocks for up to 2 seconds
    if (!ok) Serial.println("EL-Client sync failed!");
  } while(!ok);
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

  ServiceFactory::newService(DVC, 0);
  ServiceFactory::newService(SWH, new int[1]{13});
}

int data = 0x01;

void loop() {
  esp.Process();
  if(wifiConnected) {
  }
}
