//logb.h

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <time.h>
#endif

#include "RTClib.h"
#include <Wire.h>
#include <SdFat.h>

struct Settings{
  String seperate=";";
  bool toComma=true; 
  String where="";
  String pin="";
  String measurement_arduinoname="";
  int sensor_count=0;
  String device_id="logb";
  //String store[10];
  bool DB=false;
  DateTime date;
  String ArduinoName;
  unsigned long previousMillis = 0;
  unsigned long currentMillis=0;
  unsigned long firstMillis=0;
  unsigned long timeIntervall=0;
  String fulldata="";
  String cloud="";
};
extern Settings set;
DateTime NoTime();
String Time(DateTime time);
void AddData(String id, String header, String data);
void CreateName(DateTime time);
void Send();
DateTime UnixTime(int tz);
