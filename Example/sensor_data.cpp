#include "sensor_data.h"

void SENSOR_DATA::setStationId(const char* id){
      doc["station_id"] = id;
}

void SENSOR_DATA::setStationName(const char* name){
      doc["station_name"] = name;
}

void SENSOR_DATA::setStationGPS_longitude(float value){
      doc["gps_longitude"] = value;
}

void SENSOR_DATA::setStationGPS_latitude(float value){
      doc["gps_latitude"] = value;
}

String floatToString(float value) {
  char buffer[20];  // Đủ lớn để chứa chuỗi
  sprintf(buffer, "%.2f", value);
  return String(buffer);
}

void SENSOR_DATA::setValueWATER_STATION(float EC,float PH, float ORP, float TEMP){
    doc["station_id"] = "water_0001";
    doc["station_name"] = "WATER 0001";
    doc["gps_longitude"] = 106.99;
    doc["gps_latitude"] = 10.2;

    JsonArray sensors = doc["sensors"];
    sensors.clear();

    // Add EC sensor
    JsonObject ec_sensor = sensors.createNestedObject();
    ec_sensor["sensor_id"] = "ec_0001";
    ec_sensor["sensor_name"] = "EC 0001";
    ec_sensor["sensor_value"] = floatToString(EC);
    ec_sensor["sensor_unit"] = "ms/cm";

    // Add pH sensor
    JsonObject ph_sensor = sensors.createNestedObject();
    ph_sensor["sensor_id"] = "ph_0001";
    ph_sensor["sensor_name"] = "PH 0001";
    ph_sensor["sensor_value"] = floatToString(PH);
    ph_sensor["sensor_unit"] = "pH";

    // Add ORP sensor
    JsonObject orp_sensor = sensors.createNestedObject();
    orp_sensor["sensor_id"] = "ORP_0001";
    orp_sensor["sensor_name"] = "ORP 0001";
    orp_sensor["sensor_value"] = floatToString(ORP);
    orp_sensor["sensor_unit"] = "mV";

    // Add Temperature sensor
    JsonObject temp_sensor = sensors.createNestedObject();
    temp_sensor["sensor_id"] = "TEMP_0001";
    temp_sensor["sensor_name"] = "Nhiệt Độ";
    temp_sensor["sensor_value"] = floatToString(TEMP);
    temp_sensor["sensor_unit"] = "°C";
}

void SENSOR_DATA::setValueAIR_STATION(float temp, float humi, float illuminance, float co2){
      doc["station_id"] = "air_0001";
      doc["station_name"] = "AIR 0001";
      doc["gps_longitude"] = 106.89;
      doc["gps_latitude"] = 10.5;

      JsonArray sensors = doc["sensors"];
      sensors.clear();
      // Add Temperature sensor
      JsonObject temp_sensor = sensors.createNestedObject();
      temp_sensor["sensor_id"] = "temp_0001";
      temp_sensor["sensor_name"] = "Nhiệt Độ";
      temp_sensor["sensor_value"] = temp;
      temp_sensor["sensor_unit"] = "°C";

      // Add Humidity sensor
      JsonObject humi_sensor = sensors.createNestedObject();
      humi_sensor["sensor_id"] = "humi_0001";
      humi_sensor["sensor_name"] = "Độ Ẩm";
      humi_sensor["sensor_value"] = humi;
      humi_sensor["sensor_unit"] = "%";

      // Add Illuminance sensor
      JsonObject illuminance_sensor = sensors.createNestedObject();
      illuminance_sensor["sensor_id"] = "illuminance_0001";
      illuminance_sensor["sensor_name"] = "Độ Sáng";
      illuminance_sensor["sensor_value"] = illuminance;
      illuminance_sensor["sensor_unit"] = "lux";

      // Add CO2 sensor
      JsonObject co2_sensor = sensors.createNestedObject();
      co2_sensor["sensor_id"] = "CO2_0001";
      co2_sensor["sensor_name"] = "CO2";
      co2_sensor["sensor_value"] = co2;
      co2_sensor["sensor_unit"] = "ppm";
}

void SENSOR_DATA::setValueSOIL_STATION(float temp, float humi, float ph, float ec, float nito, float photpho, float kali){
      doc["station_id"] = "SOIL_0001";
      doc["station_name"] = "SOIL 0001";
      doc["gps_longitude"] = 106.89;
      doc["gps_latitude"] = 10.5;

      JsonArray sensors = doc["sensors"];
      sensors.clear();
      // Add Temperature sensor
      JsonObject temp_sensor = sensors.createNestedObject();
      temp_sensor["sensor_id"] = "temp_0001";
      temp_sensor["sensor_name"] = "Nhiệt Độ";
      temp_sensor["sensor_value"] = temp;
      temp_sensor["sensor_unit"] = "°C";

      // Add Humidity sensor
      JsonObject humi_sensor = sensors.createNestedObject();
      humi_sensor["sensor_id"] = "humi_0001";
      humi_sensor["sensor_name"] = "Độ Ẩm";
      humi_sensor["sensor_value"] = humi;
      humi_sensor["sensor_unit"] = "%";

      // Add pH sensor
      JsonObject ph_sensor = sensors.createNestedObject();
      ph_sensor["sensor_id"] = "ph_0001";
      ph_sensor["sensor_name"] = "PH";
      ph_sensor["sensor_value"] = ph;
      ph_sensor["sensor_unit"] = "";

      // Add EC sensor
      JsonObject ec_sensor = sensors.createNestedObject();
      ec_sensor["sensor_id"] = "EC_0001";
      ec_sensor["sensor_name"] = "EC";
      ec_sensor["sensor_value"] = ec;
      ec_sensor["sensor_unit"] = "ms/cm";

      // Add Nito sensor
      JsonObject nito_sensor = sensors.createNestedObject();
      nito_sensor["sensor_id"] = "Nito_0001";
      nito_sensor["sensor_name"] = "N";
      nito_sensor["sensor_value"] = nito;
      nito_sensor["sensor_unit"] = "ms/cm";

      // Add Photpho sensor
      JsonObject photpho_sensor = sensors.createNestedObject();
      photpho_sensor["sensor_id"] = "Photpho_0001";
      photpho_sensor["sensor_name"] = "P";
      photpho_sensor["sensor_value"] = photpho;
      photpho_sensor["sensor_unit"] = "ms/cm";

      // Add Kali sensor
      JsonObject kali_sensor = sensors.createNestedObject();
      kali_sensor["sensor_id"] = "Kali_0001";
      kali_sensor["sensor_name"] = "K";
      kali_sensor["sensor_value"] = kali;
      kali_sensor["sensor_unit"] = "ms/cm";
}

void SENSOR_DATA::setValueVALVE(int valve1, int valve2, int valve3){
      doc["station_id"] = "VALVE_0001";
      doc["station_name"] = "Van điện từ";
      doc["gps_longitude"] = 106.89;
      doc["gps_latitude"] = 10.5;

      JsonArray sensors = doc["sensors"];
      sensors.clear();
      // Add Valve 1
      JsonObject valve1_sensor = sensors.createNestedObject();
      valve1_sensor["sensor_id"] = "valve_0001";
      valve1_sensor["sensor_name"] = "Van nước 1";
      valve1_sensor["sensor_value"] = valve1;
      valve1_sensor["sensor_unit"] = "";

      // Add Valve 2
      JsonObject valve2_sensor = sensors.createNestedObject();
      valve2_sensor["sensor_id"] = "valve_0002";
      valve2_sensor["sensor_name"] = "Van nước 2";
      valve2_sensor["sensor_value"] = valve2;
      valve2_sensor["sensor_unit"] = "";

      // Add Valve 3
      JsonObject valve3_sensor = sensors.createNestedObject();
      valve3_sensor["sensor_id"] = "valve_003";
      valve3_sensor["sensor_name"] = "Van nước 3";
      valve3_sensor["sensor_value"] = valve3;
      valve3_sensor["sensor_unit"] = "";
}

void SENSOR_DATA::setValuePUMP(int pump1, int pump2, int pump3, int pump4, int pump5){
      doc["station_id"] = "PUMP_0001";
      doc["station_name"] = "Hệ Thống Bơm";
      doc["gps_longitude"] = 106.89;
      doc["gps_latitude"] = 10.5;

      JsonArray sensors = doc["sensors"];
      sensors.clear();
      // Add Pump 1
      JsonObject pump1_sensor = sensors.createNestedObject();
      pump1_sensor["sensor_id"] = "pump_0001";
      pump1_sensor["sensor_name"] = "Phân khu 1";
      pump1_sensor["sensor_value"] = pump1;
      pump1_sensor["sensor_unit"] = "";

      // Add Pump 2
      JsonObject pump2_sensor = sensors.createNestedObject();
      pump2_sensor["sensor_id"] = "pump_0002";
      pump2_sensor["sensor_name"] = "Phân khu 2";
      pump2_sensor["sensor_value"] = pump2;
      pump2_sensor["sensor_unit"] = "";

      // Add Pump 3
      JsonObject pump3_sensor = sensors.createNestedObject();
      pump3_sensor["sensor_id"] = "pump_0003";
      pump3_sensor["sensor_name"] = "Phân khu 2";
      pump3_sensor["sensor_value"] = pump3;
      pump3_sensor["sensor_unit"] = "";

      // Add Pump 4
      JsonObject pump4_sensor = sensors.createNestedObject();
      pump4_sensor["sensor_id"] = "pump_0004";
      pump4_sensor["sensor_name"] = "Máy bơm 1";
      pump4_sensor["sensor_value"] = pump4;
      pump4_sensor["sensor_unit"] = "";

      // Add Pump 5
      JsonObject pump5_sensor = sensors.createNestedObject();
      pump5_sensor["sensor_id"] = "pump_0005";
      pump5_sensor["sensor_name"] = "Máy bơm 2";
      pump5_sensor["sensor_value"] = pump5;
      pump5_sensor["sensor_unit"] = "";
}

void SENSOR_DATA::setROBOT_CAMERA(int dc1, int dc2, int motor1, int motor2, int motor3, int motor4){
      doc["station_id"] = "ROBOT_0001";
      doc["station_name"] = "Robot 1";
      doc["gps_longitude"] = 106.89;
      doc["gps_latitude"] = 10.5;

      JsonArray sensors = doc["sensors"];
      sensors.clear();

      // Add DC Camera 1 sensor
      JsonObject dc1_sensor = sensors.createNestedObject();
      dc1_sensor["sensor_id"] = "rc_0001";
      dc1_sensor["sensor_name"] = "Động cơ Camera 1";
      dc1_sensor["sensor_value"] = dc1;
      dc1_sensor["sensor_unit"] = "";

      // Add DC Camera 2 sensor
      JsonObject dc2_sensor = sensors.createNestedObject();
      dc2_sensor["sensor_id"] = "rc_0002";
      dc2_sensor["sensor_name"] = "Động cơ Camera 2";
      dc2_sensor["sensor_value"] = dc2;
      dc2_sensor["sensor_unit"] = "";

      // Add Motor 1 sensor
      JsonObject motor1_sensor = sensors.createNestedObject();
      motor1_sensor["sensor_id"] = "motor_0001";
      motor1_sensor["sensor_name"] = "Động cơ 1";
      motor1_sensor["sensor_value"] = motor1;
      motor1_sensor["sensor_unit"] = "";

      // Add Motor 2 sensor
      JsonObject motor2_sensor = sensors.createNestedObject();
      motor2_sensor["sensor_id"] = "motor_0002";
      motor2_sensor["sensor_name"] = "Động cơ 2";
      motor2_sensor["sensor_value"] = motor2;
      motor2_sensor["sensor_unit"] = "";

      // Add Motor 3 sensor
      JsonObject motor3_sensor = sensors.createNestedObject();
      motor3_sensor["sensor_id"] = "motor_0003";
      motor3_sensor["sensor_name"] = "Động cơ 3";
      motor3_sensor["sensor_value"] = motor3;
      motor3_sensor["sensor_unit"] = "";

      // Add Motor 4 sensor
      JsonObject motor4_sensor = sensors.createNestedObject();
      motor4_sensor["sensor_id"] = "motor_0004";
      motor4_sensor["sensor_name"] = "Động cơ 4";
      motor4_sensor["sensor_value"] = motor4;
      motor4_sensor["sensor_unit"] = "";
}

String SENSOR_DATA::getData(){
    String result;
    serializeJson(doc, result);
    return result;
}

void SENSOR_DATA::print(){
  serializeJsonPretty(doc,Serial);
  Serial.println();
}

SENSOR_DATA::SENSOR_DATA() : doc(1024) {
  doc.createNestedObject("station_id");
  doc.createNestedObject("station_name");
  doc.createNestedObject("gps_longitude");
  doc.createNestedObject("gps_latitude");
  doc.createNestedArray("sensors");
}

