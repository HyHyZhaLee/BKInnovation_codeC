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
  myMQTT.subscribe("/innovation/airmonitoring/");
  myMQTT.subscribe("/innovation/soilmonitoring/");

}

float water_EC = 0, water_PH = 0, water_ORP = 0, water_temp = 0;
float air_temperature, air_humidity, air_illuminance = 0, air_CO2 = 0;
float soil_PH = 1, soil_temperature = 2, soil_humidity = 3, soil_N = 4, soil_P = 5, soil_K= 6, soil_EC =7;





void loop() {
  // put your main code here, to run repeatedly:
  myMQTT.checkConnect();
  SENSOR_RS485 data485;

  Serial.println("Writing to air with data...");
  
  Serial2.write(data485.getDataAIR_HUMIDITY_TEMPERATURE(), 8);
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
    air_humidity = (int)receivedData[3]*256 + (int)receivedData[4];
    air_temperature = (int)receivedData[5]*256 + (int)receivedData[6];
    air_humidity/=10.0;
    air_temperature/=10.0;
    Serial.print("Air humidity: "); 
    Serial.println(air_humidity);
    Serial.print("Air temperature: ");
    Serial.println(air_temperature);
    // data.setValueAIR_STATION(air_temperature, air_humidity, air_illuminance, air_CO2);
    String temp = data.createAirStationJSON(air_temperature, air_humidity, air_illuminance, air_CO2);
    // myMQTT.publish("/innovation/airmonitoring/", data.getData().c_str()); // Publish to feed]
    myMQTT.publish("/innovation/airmonitoring/", temp); // Publish to feed
    // data.print();
    Serial.println();
  }
  delay(5000);
  myMQTT.checkConnect();


  Serial.println("Writing to soil PH with data...");
  Serial2.write(data485.getDataSOIL_PH(), 8);
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
    soil_PH = (int)receivedData[3]*256 + (int)receivedData[4];
    soil_PH/=100.0;
    Serial.print("Soil PH = ");
    Serial.println(soil_PH);
  }
  delay(1000);
  myMQTT.checkConnect();

  Serial.println("Writing to soil temperature and humidity with data...");
  Serial2.write(data485.getDataSOIL_TEMPERATURE_HUMIDITY(), 8);
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
    soil_humidity = (int)receivedData[3]*256 + (int)receivedData[4];
    soil_temperature = (int)receivedData[5]*256 + (int)receivedData[6];
    soil_humidity/=10.0;
    soil_temperature/=10.0;
    Serial.print("Soil humidity: "); 
    Serial.println(soil_humidity);
    Serial.print("Soil temperature: ");
    Serial.println(soil_temperature);
  }
  delay(1000);
  myMQTT.checkConnect();

  Serial.println("Writing to soil NPK with data...");
  Serial2.write(data485.getDataSOIL_NPK(), 8);
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
    soil_N = (int)receivedData[3]*256 + (int)receivedData[4];
    soil_P = (int)receivedData[5]*256 + (int)receivedData[6];
    soil_K = (int)receivedData[7]*256 + (int)receivedData[8];
    Serial.print("Soil Nito: "); 
    Serial.println(soil_N);
    Serial.print("Soil Photpho: ");
    Serial.println(soil_P);
    Serial.print("Soil Kali: ");
    Serial.println(soil_K);
  }
  delay(1000);
  myMQTT.checkConnect();
  

  Serial.println("Writing to soil conductivity with data...");
  Serial2.write(data485.getDataSOIL_CONDUCTIVITY(), 8);
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
    soil_EC = (int)receivedData[3]*256 + (int)receivedData[4];
    Serial.print("Soil EC: "); 
    Serial.println(soil_EC);
  }
  myMQTT.checkConnect();
  // data.setValueSOIL_STATION(soil_temperature,soil_humidity,soil_PH,soil_EC,soil_N,soil_P,soil_K);
  String data_to_pub = data.createSoilStationJSON(soil_temperature,soil_humidity,soil_PH,soil_EC,soil_N,soil_P,soil_K);
  myMQTT.publish("/innovation/soilmonitoring/", data_to_pub); // Publish to feed
  Serial.println();
  delay(5000);
  myMQTT.checkConnect();
  M5.update();
}