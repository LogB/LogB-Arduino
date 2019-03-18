//logb.h

#if defined(ESP8266)
#include "ESP8266/ESP8266WiFi.h"
#include "ESP8266/ESP8266HTTPClient.h"
#endif

#include "RTClib.h"
#include <Wire.h>
#include "SdFat/SdFat.h"

struct Settings{
  String seperate=";";
  bool toComma=false; 
  String where="";
  String pin="";
  String measurement_arduinoname="";
  int sensor_count=0;
  String device_id="logb";
  String store[10];
  String sensors[10];
  bool DB=false;
  DateTime date;
  String ArduinoName;
  unsigned long previousMillis = 0;
  unsigned long currentMillis=0;
};
extern Settings set;
String Time(DateTime time);
void AddNewSensorData(String id, String data);
void CreateName(DateTime time);
void Send();
DateTime UnixTime(int tz);
void AddNewHeaderParam(int id, String header);
