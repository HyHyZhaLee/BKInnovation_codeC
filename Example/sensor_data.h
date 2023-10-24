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
    String floatToString(float value);
    String createWaterStationJSON(float EC, float PH, float ORP, float TEMP) ;
    String createAirStationJSON(float temp, float humi, float illuminance, float co2);
    String createSoilStationJSON(float temp, float humi, float ph, float ec, float nito, float photpho, float kali);
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
