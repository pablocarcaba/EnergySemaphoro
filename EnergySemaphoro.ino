#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>
#include <String.h>

#include "config.h"
#include "ESP8266_Utils.hpp"
#include "ESP8266_Utils_OTA.hpp"
#include "Shiftbrite.hpp"


// Wifi client
WiFiClient wifiClient;
// MQTT server
PubSubClient MQTT_Client(wifiClient);
// Led
Shiftbrite led = Shiftbrite(datapin, latchpin, enablepin,clockpin); 

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length]='\0';
  String sPayload = String((char*)payload);
  float ratio=sPayload.toFloat();
  ratio=(ratio+1)/2;
  int redChanel=ratio*255;
  int greenChanel=255-(redChanel*1.25);
  if(greenChanel<0) greenChanel=0;
  Serial.print("green chanel=");Serial.println(greenChanel);
  Serial.print("red chanel=");Serial.println(redChanel);
  int color=(redChanel<<16)+(greenChanel<<8);
  led.setColor(color);
}


void setup() {
   Serial.begin(115200);
   delay(10);
   ConnectWiFiStation();
   MQTT_Client.setServer(mqtt_server, 1883);
   MQTT_Client.setCallback(callback);
   InitOTA();
}

void loop() {
if (!MQTT_Client.connected()) {
  Serial.print("Connecting ...");
    if (MQTT_Client.connect(mqttDeviceId, mqttUser, mqttPaswr)) {
      Serial.println("connected");
      MQTT_Client.subscribe(energyRatioTopic);
    } else {
      delay(500);
    }
  }
  MQTT_Client.loop();
  ArduinoOTA.handle();
  delay(250);
}
