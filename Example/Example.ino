#include <M5Atom.h>
#include "sensor_data.h"
#include "wifi_setup.h"
#include "MQTT_helper.h"

String floatToString(float value);

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


String createWaterStationJSON(float EC, float PH, float ORP, float TEMP) {
  DynamicJsonDocument doc(1024);

  doc["station_id"] = "water_0001";
  doc["station_name"] = "WATER 0001";
  doc["gps_longitude"] = 106.99;
  doc["gps_latitude"] = 10.2;

  JsonArray sensors = doc.createNestedArray("sensors");

  JsonObject ec_sensor = sensors.createNestedObject();
  ec_sensor["sensor_id"] = "ec_0001";
  ec_sensor["sensor_name"] = "EC 0001";
  ec_sensor["sensor_value"] = floatToString(EC);
  ec_sensor["sensor_unit"] = "ms/cm";

  JsonObject ph_sensor = sensors.createNestedObject();
  ph_sensor["sensor_id"] = "ph_0001";
  ph_sensor["sensor_name"] = "PH 0001";
  ph_sensor["sensor_value"] = floatToString(PH);
  ph_sensor["sensor_unit"] = "pH";

  JsonObject orp_sensor = sensors.createNestedObject();
  orp_sensor["sensor_id"] = "ORP_0001";
  orp_sensor["sensor_name"] = "ORP 0001";
  orp_sensor["sensor_value"] = floatToString(ORP);
  orp_sensor["sensor_unit"] = "mV";

  JsonObject temp_sensor = sensors.createNestedObject();
  temp_sensor["sensor_id"] = "TEMP_0001";
  temp_sensor["sensor_name"] = "Nhiệt Độ";
  temp_sensor["sensor_value"] = floatToString(TEMP);
  temp_sensor["sensor_unit"] = "°C";

  String jsonString;
  serializeJson(doc, jsonString);
  Serial.println("Data to pub:");
  serializeJsonPretty(doc, Serial);
  doc.clear();
  Serial.println();
  return jsonString;
}

String createAirStationJSON(float temp, float humi, float illuminance, float co2) {
  DynamicJsonDocument doc(1024);

  doc["station_id"] = "air_0001";
  doc["station_name"] = "AIR 0001";
  doc["gps_longitude"] = 106.89;
  doc["gps_latitude"] = 10.5;

  JsonArray sensors = doc.createNestedArray("sensors");

  JsonObject temp_sensor = sensors.createNestedObject();
  temp_sensor["sensor_id"] = "temp_0001";
  temp_sensor["sensor_name"] = "Nhiệt Độ";
  temp_sensor["sensor_value"] = floatToString(temp);
  temp_sensor["sensor_unit"] = "°C";

  JsonObject humi_sensor = sensors.createNestedObject();
  humi_sensor["sensor_id"] = "humi_0001";
  humi_sensor["sensor_name"] = "Độ Ẩm";
  humi_sensor["sensor_value"] = floatToString(humi);
  humi_sensor["sensor_unit"] = "%";

  JsonObject illuminance_sensor = sensors.createNestedObject();
  illuminance_sensor["sensor_id"] = "illuminance_0001";
  illuminance_sensor["sensor_name"] = "Độ Sáng";
  illuminance_sensor["sensor_value"] = floatToString(illuminance);
  illuminance_sensor["sensor_unit"] = "lux";

  JsonObject co2_sensor = sensors.createNestedObject();
  co2_sensor["sensor_id"] = "CO2_0001";
  co2_sensor["sensor_name"] = "CO2";
  co2_sensor["sensor_value"] = floatToString(co2);
  co2_sensor["sensor_unit"] = "ppm";

  String jsonString;
  serializeJson(doc, jsonString);
  Serial.println("Data to pub:");
  serializeJsonPretty(doc, Serial);
  doc.clear();
  Serial.println();
  return jsonString;
}
String createSoilStationJSON(float temp, float humi, float ph, float ec, float nito, float photpho, float kali) {
  DynamicJsonDocument doc(1024);

  doc["station_id"] = "SOIL_0001";
  doc["station_name"] = "SOIL 0001";
  doc["gps_longitude"] = 106.89;
  doc["gps_latitude"] = 10.5;

  JsonArray sensors = doc.createNestedArray("sensors");

  JsonObject temp_sensor = sensors.createNestedObject();
  temp_sensor["sensor_id"] = "temp_0001";
  temp_sensor["sensor_name"] = "Nhiệt Độ";
  temp_sensor["sensor_value"] = floatToString(temp);
  temp_sensor["sensor_unit"] = "°C";

  JsonObject humi_sensor = sensors.createNestedObject();
  humi_sensor["sensor_id"] = "humi_0001";
  humi_sensor["sensor_name"] = "Độ Ẩm";
  humi_sensor["sensor_value"] = floatToString(humi);
  humi_sensor["sensor_unit"] = "%";

  JsonObject ph_sensor = sensors.createNestedObject();
  ph_sensor["sensor_id"] = "ph_0001";
  ph_sensor["sensor_name"] = "PH";
  ph_sensor["sensor_value"] = floatToString(ph);
  ph_sensor["sensor_unit"] = "";

  JsonObject ec_sensor = sensors.createNestedObject();
  ec_sensor["sensor_id"] = "EC_0001";
  ec_sensor["sensor_name"] = "EC";
  ec_sensor["sensor_value"] = floatToString(ec);
  ec_sensor["sensor_unit"] = "ms/cm";

  JsonObject nito_sensor = sensors.createNestedObject();
  nito_sensor["sensor_id"] = "Nito_0001";
  nito_sensor["sensor_name"] = "N";
  nito_sensor["sensor_value"] = floatToString(nito);
  nito_sensor["sensor_unit"] = "ms/cm";

  JsonObject photpho_sensor = sensors.createNestedObject();
  photpho_sensor["sensor_id"] = "Photpho_0001";
  photpho_sensor["sensor_name"] = "P";
  photpho_sensor["sensor_value"] = floatToString(photpho);
  photpho_sensor["sensor_unit"] = "ms/cm";

  JsonObject kali_sensor = sensors.createNestedObject();
  kali_sensor["sensor_id"] = "Kali_0001";
  kali_sensor["sensor_name"] = "K";
  kali_sensor["sensor_value"] = floatToString(kali);
  kali_sensor["sensor_unit"] = "ms/cm";

  String jsonString;
  serializeJson(doc, jsonString);
  Serial.println("Data to pub:");
  serializeJsonPretty(doc, Serial);
  doc.clear();
  Serial.println();
  return jsonString;
}


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
    String temp = createAirStationJSON(air_temperature, air_humidity, air_illuminance, air_CO2);
    // myMQTT.publish("/innovation/airmonitoring/", data.getData().c_str()); // Publish to feed]
    myMQTT.publish("/innovation/airmonitoring/", temp); // Publish to feed
    // data.print();
    Serial.println();
  }
  delay(5000);

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
  delay(5000);

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
  delay(5000);

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
  delay(5000);
  

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
  // data.setValueSOIL_STATION(soil_temperature,soil_humidity,soil_PH,soil_EC,soil_N,soil_P,soil_K);
  String data_to_pub = createSoilStationJSON(soil_temperature,soil_humidity,soil_PH,soil_EC,soil_N,soil_P,soil_K);
  myMQTT.publish("/innovation/soilmonitoring/", data_to_pub); // Publish to feed
  Serial.println();
  delay(5000);
  M5.update();
}














  // int input = Serial.read();
  // if (input == 'j') {
  //   data.setValueWATER_STATION(112.3, 113.4, 114.3, 113.2);
  //   myMQTT.publish("/innovation/watermonitoring/", data.getData().c_str()); // Publish to feed
  //   Serial.println("Data to pub:");
  //   data.print();
  //   Serial.println();
  // }
  // if (input == 'k') {
  //   data.setValueAIR_STATION(30.1, 30.1, 30.1, 30.1);
  //   myMQTT.publish("/innovation/airmonitoring/", data.getData().c_str()); // Publish to feed
  //   Serial.println("Data to pub:");
  //   data.print();
  //   Serial.println();
  // }
  // if (input == 'l'){
  //   data.setValueSOIL_STATION(10.1,11.2,12.3,13.4,14.5,15.6,16.7);
  //   myMQTT.publish("/innovation/airmonitoring/", data.getData().c_str()); // Publish to feed
  //   Serial.println("Data to pub:");
  //   data.print();
  //   Serial.println();
  // }
  // if (input == 'z') {
  //   Serial.println("Writing to soil PH with data...");
  //   SENSOR_RS485 data485;
  //   uint8_t* data = data485.getDataSOIL_PH();
  //   Serial2.write(data, 8);
  //   delay(1000);
  //   if (Serial2.available()) {    // If the serial port receives a message. 
  //     uint8_t receivedData[7];
  //     Serial2.readBytes(receivedData, sizeof(receivedData));  // Read the message.
  //     for (int i = 0; i <7 ; i++) {
  //       Serial.print("0x");
  //       Serial.print(receivedData[i], HEX);
  //       Serial.print(", ");
  //     }
  //     Serial.println();
  //     float PH = (int)receivedData[3]*256 + (int)receivedData[4];
  //     PH/=100.0;
  //     Serial.print("PH = ");
  //     Serial.println(PH);
  //   }
  // }
  // if (input == 'x') {
  //   Serial.println("Writing to soil temperature and humidity with data...");
  //   SENSOR_RS485 data485;
  //   uint8_t* data = data485.getDataSOIL_TEMPERATURE_HUMIDITY();
  //   Serial2.write(data, 8);
  //   delay(1000);
  //   if (Serial2.available()) {    // If the serial port receives a message. 
  //     uint8_t receivedData[9];
  //     Serial2.readBytes(receivedData, sizeof(receivedData));  // Read the message.
  //     for (int i = 0; i <9 ; i++) {
  //       Serial.print("0x");
  //       Serial.print(receivedData[i], HEX);
  //       Serial.print(", ");
  //     }
  //     Serial.println();
  //     float humidity = (int)receivedData[3]*256 + (int)receivedData[4];
  //     float temperature = (int)receivedData[5]*256 + (int)receivedData[6];
  //     humidity/=10.0;
  //     temperature/=10.0;
  //     Serial.print("Soil humidity: "); 
  //     Serial.println(humidity);
  //     Serial.print("Soil temperature: ");
  //     Serial.println(temperature);
  //   }
  // }
  // if (input == 'c') {
  //   Serial.println("Writing to soil NPK with data...");
  //   SENSOR_RS485 data485;
  //   uint8_t* data = data485.getDataSOIL_NPK();
  //   Serial2.write(data, 8);
  //   delay(1000);
  //   if (Serial2.available()) {    // If the serial port receives a message. 
  //     uint8_t receivedData[11];
  //     Serial2.readBytes(receivedData, sizeof(receivedData));  // Read the message.
  //     for (int i = 0; i <11 ; i++) {
  //       Serial.print("0x");
  //       Serial.print(receivedData[i], HEX);
  //       Serial.print(", ");
  //     }
  //     Serial.println();
  //     float N = (int)receivedData[3]*256 + (int)receivedData[4];
  //     float P = (int)receivedData[5]*256 + (int)receivedData[6];
  //     float K = (int)receivedData[7]*256 + (int)receivedData[8];
  //     Serial.print("Soil Nito: "); 
  //     Serial.println(N);
  //     Serial.print("Soil Photpho: ");
  //     Serial.println(P);
  //     Serial.print("Soil Kali: ");
  //     Serial.println(K);
  //   }
  // }
  // if (input == 'v') {
  //   Serial.println("Writing to soil conductivity with data...");
  //   SENSOR_RS485 data485;
  //   uint8_t* data = data485.getDataSOIL_CONDUCTIVITY();
  //   Serial2.write(data, 8);
  //   delay(1000);
  //   if (Serial2.available()) {    // If the serial port receives a message. 
  //     uint8_t receivedData[7];
  //     Serial2.readBytes(receivedData, sizeof(receivedData));  // Read the message.
  //     for (int i = 0; i <7 ; i++) {
  //       Serial.print("0x");
  //       Serial.print(receivedData[i], HEX);
  //       Serial.print(", ");
  //     }
  //     Serial.println();
  //     float ec = (int)receivedData[3]*256 + (int)receivedData[4];
  //     Serial.print("Soil EC: "); 
  //     Serial.println(ec);
  //   }
  // }
  // if (input == 'b'){
  //   Serial.println("Writing to air with data...");
  //   SENSOR_RS485 data485;
  //   uint8_t* data = data485.getDataAIR_HUMIDITY_TEMPERATURE();
  //   Serial2.write(data, 8);
  //   delay(1000);
  //   if (Serial2.available()) {    // If the serial port receives a message. 
  //     uint8_t receivedData[9];
  //     Serial2.readBytes(receivedData, sizeof(receivedData));  // Read the message.
  //     for (int i = 0; i <9 ; i++) {
  //       Serial.print("0x");
  //       Serial.print(receivedData[i], HEX);
  //       Serial.print(", ");
  //     }
  //     Serial.println();
  //     float humidity = (int)receivedData[3]*256 + (int)receivedData[4];
  //     float temperature = (int)receivedData[5]*256 + (int)receivedData[6];
  //     humidity/=10.0;
  //     temperature/=10.0;
  //     Serial.print("Air humidity: "); 
  //     Serial.println(humidity);
  //     Serial.print("Air temperature: ");
  //     Serial.println(temperature);
  //   }
  // }
