//logb.h

#if defined(ESP8266)

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <time.h>
#endif

#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>
#include <SdFat.h>

struct Settings{
  String file=""; 
  String semicolon=";";
  bool toComma=true; 
  String where="";
  String pin="";
  String date="";
  int db=0;
  int now=1;
  String device="";
  String store[25];
  unsigned long previousMillis = 0;
  unsigned long timeInterval= 1000;
  unsigned long currentMillis=0;
};
extern Settings set;
void dateTime(uint16_t* date, uint16_t* time);
void out(String data);
String Date();
String GPSread();
String fileNameCreate();
void timeSetting();
String Time();
String DIPconfig();
long int interval(String b);
void databaseCreate();
String onlineDate(int tz);
int upload();
String TableName(int tz);
void connectToDB();
void getData(String data);
