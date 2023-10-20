#include <M5Atom.h>
#include "wifi_setup.h"
#include "MQTT_helper.h"

//Class Wifi_esp32
Wifi_esp32 wifi;
//Class MyMQTT
MyMQTT myMQTT("mqttserver.tk", "innovation", "Innovation_RgPQAZoA5N");
void setup() {
  // put your setup code here, to run once:
  M5.begin(true, false, true);
  wifi.setupWifi(); //Setup wifi
  myMQTT.connectToMQTT(); // Kết nối MQTT với server
  myMQTT.subscribe("/innovation/soilmonitoring/"); //Sub to feed
}

int counter = 0;
void loop() {
  // put your main code here, to run repeatedly:
  myMQTT.checkConnect();
  Serial.print("Counter = ");
  Serial.println(counter);
  String data = "{\"counter\":" + String(counter++) + "}";

  myMQTT.publish("/innovation/soilmonitoring/", data); //Pub to feed

  delay(5000);
  M5.update();
}
