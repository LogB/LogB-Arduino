//logb.h


#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#endif
#include <time.h>
#include "RTClib.h"
#include <Wire.h>
#include <SdFat.h>

struct Settings{
  String seperate=";";
  bool toComma=false; 
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
  unsigned long timeInterval=0;
  String fulldata="";
  String cloud="";
};
void GSMBegin();
DateTime UnixWithGSM(int tz);
extern Settings set;
DateTime NoTime();
String Time(DateTime time);
void AddData(String id, String header, String data);
void CreateName(DateTime time);
void Send();
DateTime UnixTime(int tz);
