/*
 * sensor_data.h
 *
 *  Created on: Oct 23, 2023
 *      Author: Huy Ly
 */

#include "sensor_data.h"

String SENSOR_DATA::floatToString(float value) {
  char buffer[20];  // Đủ lớn để chứa chuỗi
  sprintf(buffer, "%.2f", value);
  return String(buffer);
}
String SENSOR_DATA::createWaterStationJSON(float EC, float PH, float ORP, float TEMP) {
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
String SENSOR_DATA::createAirStationJSON(float temp, float humi, float illuminance, float co2) {
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
String SENSOR_DATA::createSoilStationJSON(float temp, float humi, float ph, float ec, float nito, float photpho, float kali) {
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

///////////////////////////////////////

SENSOR_RS485::SENSOR_RS485(){
  data_air_humidity_temperature = new uint8_t[8]{0x14, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC6, 0xCE};

  data_soil_PH = new uint8_t[8]{0x01, 0x03, 0x00, 0x06, 0x00, 0x01, 0x64, 0x0B};
  data_soil_temp_and_humi = new uint8_t[8]{0x01, 0x03, 0x00, 0x12, 0x00, 0x02, 0x64, 0x0E};
  data_soil_npk = new uint8_t[8]{0x01, 0x03, 0x00, 0x1E, 0x00, 0x03, 0x65, 0xCD};
  data_soil_conductivity = new uint8_t[8]{0x01, 0x03, 0x00, 0x15, 0x00, 0x01, 0x95, 0xCE};

  data_water_ec = new uint8_t[8]{0x04, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x5E};
  data_water_ph = new uint8_t[8]{0x04, 0x03, 0x00, 0x08, 0x00, 0x02, 0x45, 0x9C};
  data_water_orp = new uint8_t[8]{0x05, 0x03, 0x00, 0x01, 0x00, 0x02, 0x94, 0x4F};
  data_water_temp = new uint8_t[8]{0x05, 0x03, 0x00, 0x03, 0x00, 0x02, 0x35, 0x8F};
  data_water_air = new uint8_t[8]{0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B};
};

SENSOR_RS485::~SENSOR_RS485() {
  delete[] data_air_humidity_temperature;
  delete[] data_soil_PH;
  delete[] data_soil_temp_and_humi;
  delete[] data_soil_npk;
  delete[] data_soil_conductivity;
  delete[] data_water_ec;
  delete[] data_water_ph;
  delete[] data_water_orp;
  delete[] data_water_temp;
  delete[] data_water_air;
};

uint8_t* SENSOR_RS485::getDataAIR_HUMIDITY_TEMPERATURE(){
  return data_air_humidity_temperature;
};

uint8_t* SENSOR_RS485::getDataSOIL_PH(){
  return data_soil_PH;
};

uint8_t* SENSOR_RS485::getDataSOIL_TEMPERATURE_HUMIDITY(){
  return data_soil_temp_and_humi;
};

uint8_t* SENSOR_RS485::getDataSOIL_NPK(){
  return data_soil_npk;
};

uint8_t* SENSOR_RS485::getDataSOIL_CONDUCTIVITY(){
  return data_soil_conductivity;
};

uint8_t* SENSOR_RS485::getDataWATER_EC(){
  return data_water_ec;
};

uint8_t* SENSOR_RS485::getDataWATER_PH(){
  return data_water_ph;
};

uint8_t* SENSOR_RS485::getDataWATER_ORP(){
  return data_water_orp;
};

uint8_t* SENSOR_RS485::getDataWATER_TEMP(){
  return data_water_temp;
};

uint8_t* SENSOR_RS485::getDataWATER_AIR(){
  return data_water_air;
};
