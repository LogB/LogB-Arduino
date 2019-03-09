//logb.h

#if defined(ESP8266)

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#endif
#include <time.h>
#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>
#include <SdFat.h>

struct Settings{
  String file=""; 
  String seperate=";";
  bool toComma=true; 
  String where="";
  String pin="";
  String measurement_arduinoname="";
  int sensor_count=0;
  String device_id="";
  String store[25];
  String sensors[25];
  String header[25];
  unsigned long previousMillis = 0;
  unsigned long timeInterval= 1000;
  unsigned long currentMillis=0;
  //time_t time;
  int now=0;
  bool DB=false;
  String date;
  String ArduinoName;
};
extern Settings set;
void Time(time_t time);
void AddNewSensorData(String id, String data);
void CreateName(time_t time);
void Send();
time_t UnixTime(int tz);
void AddNewHeaderParam(String id, String header);
