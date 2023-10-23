#include <M5Atom.h>
#include "wifi_setup.h"
#include "MQTT_helper.h"
#include "sensor_data.h"

// Class Wifi_esp32
Wifi_esp32 wifi;
// Class MyMQTT
MyMQTT myMQTT("mqttserver.tk", "innovation", "Innovation_RgPQAZoA5N");
// Class data json already created
SENSOR_DATA data;

void setup() {
  // put your setup code here, to run once:
  M5.begin(true, false, true);
  Serial2.begin(9600, SERIAL_8N1, 22, 19);
  wifi.setupWifi(); // Setup wifi
  myMQTT.connectToMQTT(); // Connect to MQTT server
  myMQTT.subscribe("/innovation/watermonitoring/"); // Subscribe to the feed
}


uint8_t data_ec[] = {0x04, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x5E};
uint8_t data_ph[] = {0x04, 0x03, 0x00, 0x08, 0x00, 0x02, 0x45, 0x9C};
uint8_t data_orp[] = {0x05, 0x03, 0x00, 0x01, 0x00, 0x02, 0x94, 0x4F};
uint8_t data_temp[] = {0x05, 0x03, 0x00, 0x03, 0x00, 0x02, 0x35, 0x8F};
uint8_t data_air[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B};

float ec;
float ph;
float orp;
float temp;


void loop() {
  // put your main code here, to run repeatedly:
  myMQTT.checkConnect();
  int input = Serial.read();
  if (input == 'j') {
    data.setValueWATER_STATION(112.3, 113.4, 114.3, 113.2);
    myMQTT.publish("/innovation/watermonitoring/", data.getData().c_str()); // Publish to feed
    Serial.println("Data to pub:");
    data.print();
    Serial.println();
  }
  if (input == 'z') {
    Serial.println("Writing to EC...");
    Serial2.write(data_ec, sizeof(data_ec));
    M5.update();
  }
  if (input == 'x') {
    Serial.println("Writing to ORP...");
    Serial2.write(data_orp, sizeof(data_orp));
    M5.update();
  }
  if (input == 'c') {
    Serial.println("Writing to PH...");
    Serial2.write(data_ph, sizeof(data_ph));
    M5.update();
  }
  if (input == 'v') {
    Serial.println("Writing to TEMP...");
    Serial2.write(data_temp, sizeof(data_temp));
    M5.update();

  }
  if (input == 'b'){
    Serial.println("Writing to air...");
    Serial2.write(data_air, sizeof(data_air));

  }
  if (Serial2.available()) {    // If the serial port receives a message. 
      uint8_t receivedData[10];
      Serial2.readBytes(receivedData, sizeof(receivedData));  // Read the message.
      for (int i = 0; i < 8; i++) {
        Serial.print("0x");
        Serial.print(receivedData[i], HEX);
        Serial.print(", ");
      }
      Serial.println();
      // float humidity = (int)receivedData[3]*256 + (int)receivedData[4];
      // float temperature = (int)receivedData[5]*256 + (int)receivedData[6];
      // humidity/=10.0;
      // temperature/=10.0;
      // Serial.print("Humidity: "); 
      // Serial.println(humidity);
      // Serial.print("Temperature: ");
      // Serial.println(temperature);
      M5.update();
  }
  M5.update();
}
