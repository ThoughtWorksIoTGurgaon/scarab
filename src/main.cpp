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
      softwareSerial.println("WIFI CONNECTED");
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
  softwareSerial.println("Connected");
  // mqtt.subscribe("/topic/0"); //or mqtt.subscribe("topic"); /*with qos = 0*/
  // mqtt.subscribe("/topic/1");
  // mqtt.subscribe("/topic/2");
  mqtt.subscribe("/device/my-device-id/cmd");
}
void mqttDisconnected(void* response)
{

}
void mqttData(void* response)
{
  RESPONSE res(response);

  softwareSerial.print("Received: topic=");
  String topic = res.popString();
  softwareSerial.println(topic);

  softwareSerial.print("data=");
  String data = res.popString();

  Service::process(Packet::parse(data.c_str()));

  softwareSerial.println(data);
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

  softwareSerial.println("ARDUINO: setup mqtt client");
  if(!mqtt.begin("DVES_duino", "", "", 120, 1)) {
    softwareSerial.println("ARDUINO: fail to setup mqtt");
    while(1);
  }

  softwareSerial.println("ARDUINO: setup mqtt lwt");
  mqtt.lwt("/lwt", "offline", 0, 0); //or mqtt.lwt("/lwt", "offline");

/*setup mqtt events */
  mqtt.connectedCb.attach(&mqttConnected);
  mqtt.disconnectedCb.attach(&mqttDisconnected);
  mqtt.publishedCb.attach(&mqttPublished);
  mqtt.dataCb.attach(&mqttData);

  /*setup wifi*/
  softwareSerial.println("ARDUINO: setup wifi");
  esp.wifiCb.attach(&wifiCb);

  esp.wifiConnect("XT1033","12345678");

  softwareSerial.println("ARDUINO: system started");

  pinMode(13, OUTPUT);


  ServiceFactory::newService(SWH, new int[1]{13});
  // ServiceFactory::newService(SWH, new int[1]{14});
  // ServiceFactory::newService(SWH, new int[1]{15});
  // ServiceFactory::newService(SWH, new int[1]{16});
}

int data = 0x01;

void loop() {
  esp.process();
  if(wifiConnected) {

  }

  // delay(1000);
  //
  // data = data == 0x01 ? 0x02 : 0x01;
  //
  // char packet[] = {
  //   0x01, 0x01, 0x01,0x01,0x01,
  //   0x01,
  //   0x01,
  //   0x01, 0x01, data,
  //   0x00
  // };
  //
  // WritePacket *pkt = Packet::parse(packet);
  // Serial.println(pkt->serviceId);
  // Service::process(pkt);
}
