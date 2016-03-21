/**
 * \file
 *       ESP8266 MQTT Bridge example
 * \author
 *       Tuan PM <tuanpm@live.com>
 */
#include "Arduino.h"
#include <SoftwareSerial.h>
#include "espduino.h"
#include <mqtt.h>
#include "ServiceFactory.h"

SoftwareSerial softwareSerial(2, 3); // RX, TX
ESP esp(&softwareSerial, &Serial, 4);
MQTT mqtt(&esp);

boolean wifiConnected = false;

void wifiCb(void* response)
{
  uint32_t status;
  RESPONSE res(response);
  Serial.println("Wifi Connected");
  if(res.getArgc() == 1) {
    res.popArgs((uint8_t*)&status, 4);
    if(status == STATION_GOT_IP) {
      Serial.println("WIFI CONNECTED");
      mqtt.connect("192.168.43.11", 1883, false);
      wifiConnected = true;
      //or mqtt.connect("host", 1883); /*without security ssl*/
    } else {
      wifiConnected = false;
      mqtt.disconnect();
    }
  }
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
  RESPONSE res(response);

  Serial.print("Received: topic=");
  String topic = res.popString();
  Serial.println(topic);

  Serial.print("data=");
  String data = res.popString();

  Service::process(Packet::parseWrite(data.c_str()));

  Serial.println(data);
}
void mqttPublished(void* response)
{

}
void setup() {
  Serial.begin(19200);
  softwareSerial.begin(19200);
  esp.enable();
  delay(500);
  esp.reset();
  delay(500);
  while(!esp.ready());

  Serial.println("ARDUINO: setup mqtt client");
  if(!mqtt.begin("my-device-id", "", "", 120, 1)) {
    Serial.println("ARDUINO: fail to setup mqtt");
    while(1);
  }

  Serial.println("ARDUINO: setup mqtt lwt");
  mqtt.lwt("/lwt", "offline", 0, 0); //or mqtt.lwt("/lwt", "offline");

/*setup mqtt events */
  mqtt.connectedCb.attach(&mqttConnected);
  mqtt.disconnectedCb.attach(&mqttDisconnected);
  mqtt.publishedCb.attach(&mqttPublished);
  mqtt.dataCb.attach(&mqttData);

  /*setup wifi*/
  Serial.println("ARDUINO: setup wifi");
  esp.wifiCb.attach(&wifiCb);

  esp.wifiConnect("XT1033","12345678");

  Serial.println("ARDUINO: system started");

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  ServiceFactory::newService(DVC, 0);
  ServiceFactory::newService(SWH, new int[1]{13});
}

int data = 0x01;

void loop() {
  esp.process();
  if(wifiConnected) {
  }
}
