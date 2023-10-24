/*
 * sensor_data.h
 *
 *  Created on: Oct 23, 2023
 *      Author: Huy Ly
 */

#ifndef INC_SENSOR_DATA_H_
#define INC_SENSOR_DATA_H_

#include <ArduinoJson.h>

class SENSOR_DATA{
  public:
    SENSOR_DATA(){};
    String floatToString(float value) {
      char buffer[20];  // Đủ lớn để chứa chuỗi
      sprintf(buffer, "%.2f", value);
      return String(buffer);
    }
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
};

class SENSOR_RS485{
  private:
    uint8_t* data_air_humidity_temperature;
    uint8_t* data_soil_PH;
    uint8_t* data_soil_temp_and_humi;
    uint8_t* data_soil_npk;
    uint8_t* data_soil_conductivity;
    uint8_t* data_water_ec;
    uint8_t* data_water_ph;
    uint8_t* data_water_orp;
    uint8_t* data_water_temp;
    uint8_t* data_water_air;

  public:
    SENSOR_RS485();
    ~SENSOR_RS485();
    uint8_t* getDataAIR_HUMIDITY_TEMPERATURE();
    uint8_t* getDataSOIL_PH();
    uint8_t* getDataSOIL_TEMPERATURE_HUMIDITY();
    uint8_t* getDataSOIL_NPK();
    uint8_t* getDataSOIL_CONDUCTIVITY();
    uint8_t* getDataWATER_EC();
    uint8_t* getDataWATER_PH();
    uint8_t* getDataWATER_ORP();
    uint8_t* getDataWATER_TEMP();
    uint8_t* getDataWATER_AIR();
};

#endif
