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
#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>
#include <SdFat.h>

struct Settings{
  String file=""; 
  String seperate=";";
  bool toComma=false; 
  String where="";
  String pin="";
  String measurement_arduinoname="";
  int sensor_count=0;
  String device_id="logb";
  String store[25];
  String sensors[25];
  String header[25];
  unsigned long previousMillis = 0;
  unsigned long timeInterval= 1000;
  unsigned long currentMillis=0;
  bool DB=false;
  String date;
  String ArduinoName;
};
extern Settings set;
void Time(DateTime time);
void AddNewSensorData(String id, String data);
void CreateName(DateTime time);
void Send();
DateTime UnixTime(int tz);
void AddNewHeaderParam(String id, String header);
