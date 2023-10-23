#ifndef INC_SENSOR_DATA_H_
#define INC_SENSOR_DATA_H_

#include <ArduinoJson.h>

class SENSOR_DATA{
  private:
    DynamicJsonDocument doc;
  public:
    SENSOR_DATA();

    void setStationId(const char* id);
    void setStationName(const char* name);
    void setStationGPS_longitude(float value);
    void setStationGPS_latitude(float value);
    void setValueWATER_STATION(float EC,float PH, float ORP, float TEMP);
    void setValueAIR_STATION(float temp, float humi, float illuminance, float co2);
    void setValueSOIL_STATION(float temp, float humi, float ph, float ec, float nito, float photpho, float kali);
    void setValueVALVE(int valve1, int valve2, int valve3);
    void setValuePUMP(int pump1, int pump2, int pump3, int pump4, int pump5);
    void setROBOT_CAMERA(int dc1, int dc2, int motor1, int motor2, int motor3, int motor4);

    String getData();

    void print();
};


#endif
