//logb.h

#if defined(ESP8266)

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#endif

#include "Adafruit_SI1145.h"
#include "Adafruit_BMP085.h"
#include "RTClib.h"
#include "BH1750.h"
#include "Sodaq_SHT2x.h"

#include <time.h>
//#include <SPI.h>
//#include <Arduino.h>
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
  String store[10];
  int sensors[10];
  //String header[10];
  bool DB=false;
  DateTime date;
  String ArduinoName;
};
extern Settings set;
String Time(DateTime time);
void AddNewSensorData(int id, String data);
void CreateName(DateTime time);
void Send();
DateTime UnixTime(int tz);
void AddNewHeaderParam(int id, String header);
