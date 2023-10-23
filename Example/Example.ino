#include <M5Atom.h>
#include "sensor_data.h"
#include "wifi_setup.h"
#include "MQTT_helper.h"


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
    Serial.println("Writing to soil PH with data...");
    SENSOR_RS485 data485;
    uint8_t* data = data485.getDataSOIL_PH();
    Serial2.write(data, 8);
    delay(1000);
    if (Serial2.available()) {    // If the serial port receives a message. 
      uint8_t receivedData[7];
      Serial2.readBytes(receivedData, sizeof(receivedData));  // Read the message.
      for (int i = 0; i <7 ; i++) {
        Serial.print("0x");
        Serial.print(receivedData[i], HEX);
        Serial.print(", ");
      }
      Serial.println();
      float PH = (int)receivedData[3]*256 + (int)receivedData[4];
      PH/=100.0;
      Serial.print("PH = ");
      Serial.println(PH);
    }
  }
  if (input == 'x') {
    Serial.println("Writing to soil temperature and humidity with data...");
    SENSOR_RS485 data485;
    uint8_t* data = data485.getDataSOIL_TEMPERATURE_HUMIDITY();
    Serial2.write(data, 8);
    delay(1000);
    if (Serial2.available()) {    // If the serial port receives a message. 
      uint8_t receivedData[9];
      Serial2.readBytes(receivedData, sizeof(receivedData));  // Read the message.
      for (int i = 0; i <9 ; i++) {
        Serial.print("0x");
        Serial.print(receivedData[i], HEX);
        Serial.print(", ");
      }
      Serial.println();
      float humidity = (int)receivedData[3]*256 + (int)receivedData[4];
      float temperature = (int)receivedData[5]*256 + (int)receivedData[6];
      humidity/=10.0;
      temperature/=10.0;
      Serial.print("Soil humidity: "); 
      Serial.println(humidity);
      Serial.print("Soil temperature: ");
      Serial.println(temperature);
    }
  }
  if (input == 'c') {
    Serial.println("Writing to soil NPK with data...");
    SENSOR_RS485 data485;
    uint8_t* data = data485.getDataSOIL_NPK();
    Serial2.write(data, 8);
    delay(1000);
    if (Serial2.available()) {    // If the serial port receives a message. 
      uint8_t receivedData[11];
      Serial2.readBytes(receivedData, sizeof(receivedData));  // Read the message.
      for (int i = 0; i <11 ; i++) {
        Serial.print("0x");
        Serial.print(receivedData[i], HEX);
        Serial.print(", ");
      }
      Serial.println();
      float N = (int)receivedData[3]*256 + (int)receivedData[4];
      float P = (int)receivedData[5]*256 + (int)receivedData[6];
      float K = (int)receivedData[7]*256 + (int)receivedData[8];
      Serial.print("Soil Nito: "); 
      Serial.println(N);
      Serial.print("Soil Photpho: ");
      Serial.println(P);
      Serial.print("Soil Kali: ");
      Serial.println(K);
    }
  }
  if (input == 'v') {
    Serial.println("Writing to soil conductivity with data...");
    SENSOR_RS485 data485;
    uint8_t* data = data485.getDataSOIL_CONDUCTIVITY();
    Serial2.write(data, 8);
    delay(1000);
    if (Serial2.available()) {    // If the serial port receives a message. 
      uint8_t receivedData[7];
      Serial2.readBytes(receivedData, sizeof(receivedData));  // Read the message.
      for (int i = 0; i <7 ; i++) {
        Serial.print("0x");
        Serial.print(receivedData[i], HEX);
        Serial.print(", ");
      }
      Serial.println();
      float ec = (int)receivedData[3]*256 + (int)receivedData[4];
      Serial.print("Soil EC: "); 
      Serial.println(ec);
    }
  }
  if (input == 'b'){
    Serial.println("Writing to air with data...");
    SENSOR_RS485 data485;
    uint8_t* data = data485.getDataAIR_HUMIDITY_TEMPERATURE();
    Serial2.write(data, 8);
    delay(1000);
    if (Serial2.available()) {    // If the serial port receives a message. 
      uint8_t receivedData[9];
      Serial2.readBytes(receivedData, sizeof(receivedData));  // Read the message.
      for (int i = 0; i <9 ; i++) {
        Serial.print("0x");
        Serial.print(receivedData[i], HEX);
        Serial.print(", ");
      }
      Serial.println();
      float humidity = (int)receivedData[3]*256 + (int)receivedData[4];
      float temperature = (int)receivedData[5]*256 + (int)receivedData[6];
      humidity/=10.0;
      temperature/=10.0;
      Serial.print("Air humidity: "); 
      Serial.println(humidity);
      Serial.print("Air temperature: ");
      Serial.println(temperature);
    }
  }
  M5.update();
}

