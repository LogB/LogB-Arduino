//logb.cpp
#define TINY_GSM_MODEM_SIM800 
#include <TinyGsmClient.h>
#include <ArduinoHttpClient.h>
#include <SoftwareSerial.h>
#include "logb.h"
SdFat SD;


#define SerialAT Serial2
//SoftwareSerial SerialAT(2, 3);
String contentType = "application/x-www-form-urlencoded";
char apn[] = "internet";
char gprsUser[] = "";
char gprsPass[] = "";
char server[] = "api.logb.hu";
char api[] = "/v1.1/upload.php";
char t[] = "/v1.1/time.php";
int port = 80;


TinyGsm modem(SerialAT);
TinyGsmClient client(modem);
HttpClient http(client, server, port);

#if defined(ESP8266)
HTTPClient http; 
#endif

DateTime NoTime(){
  return 1702511185;
}

DateTime UnixTime(int tz){
  #if defined(ESP8266)
  time_t now=0;
  int timezone = tz * 3600;
  while(now<958881900){
  configTime(timezone, 0 , "pool.ntp.org","time.nist.gov","time.windows.com");
  while(!time(nullptr)){
  }delay(50);
now = time(nullptr);
  }
return now;
#endif
}

void GSMBegin(){
  SerialAT.begin(115200);
  modem.init();
}
DateTime UnixWithGSM(int tz){
  String time="";
  if (!modem.gprsConnect(apn))
        {
          return;
        }
        if (!modem.waitForNetwork())
        {
          return;
        }
        if (!modem.gprsConnect(apn, gprsUser, gprsPass))
        {
          return;
        }
        if (!client.connect(server, port))
        {
          return;
        }
       http.post(t, contentType,"tz="+tz);
       unsigned long timeout = millis();
 
  while (client.connected() && millis() - timeout < 10000L) //IDK why this is needed, maybe waits until the connection closes?
  {
    while (client.available())
    {
      time += client.read();
      timeout = millis();
    }
  }
 
  // Shutdown
  http.stop();
  client.stop();
  modem.gprsDisconnect();
  return time.toInt();
}

void CreateName(DateTime time){
  set.ArduinoName=set.device_id+"_"+String(time.unixtime());
}

String wz(int n){
  String r="0";
  if(n<10){
    r+=n;
  }else{
    r=n;
  }return r;
}
String Time(DateTime time){
 String date="";
 set.date=time;
 if(time.unixtime()== 1702511185){
  unsigned long m = set.previousMillis-set.firstMillis;
  date=String(m/1000)+"."+String((m-m/1000*1000)/100);
 }else{
  date+=time.year();  
  date+="-";
  date+=wz(time.month());
  date+="-";
  date+=wz(time.day());
  date+=" ";
  date+=wz(time.hour());
  date+=":";
  date+=wz(time.minute());
  date+=":";
  date+=wz(time.second());
 }
return date;
}

void dateTime(uint16_t* date, uint16_t* time) {
  DateTime now = set.date;
  *date = FAT_DATE(now.year(), now.month(), now.day());
  *time = FAT_TIME(now.hour(), now.minute(), now.second());
}

void Send(){
  set.cloud+="oszlop="+String(set.sensor_count)+"&ma="+set.ArduinoName+"&pin="+set.pin+"&device="+set.device_id+"&time="+Time(set.date);
  if(set.toComma){
  set.fulldata.replace('.',',');
   } 
    for (int j = 0; j < set.where.length(); j++){
      char w = set.where.charAt(j);
       
      if (w=='a'){
      Serial.println(set.fulldata);
      }

      if (w=='b'){
      SdFile::dateTimeCallback(dateTime);
          if(set.DB==false){
          SD.begin(SS);
          }
          String file=set.ArduinoName+".txt";
          File Sd = SD.open(file, FILE_WRITE);
            if(Sd){
              Sd.println(set.fulldata);
            }
            Sd.close();
        }
        
      if(w=='c'){
           #if defined(ESP8266)
            http.begin("http://api.logb.hu/v1.1/upload.php");
            http.addHeader("Content-Type", "application/x-www-form-urlencoded");
            int httpCode=http.POST(set.cloud);
            http.end();
            //Serial.println(httpCode);
           #endif
        }
      if(w=='d'){
        if (!modem.gprsConnect(apn))
        {
          return;
        }
        if (!modem.waitForNetwork())
        {
          return;
        }
        if (!modem.gprsConnect(apn, gprsUser, gprsPass))
        {
          return;
        }
        if (!client.connect(server, port))
        {
          return;
        }
       http.post(api, contentType, set.cloud);
       unsigned long timeout = millis();
 
  while (client.connected() && millis() - timeout < 10000L) //IDK why this is needed, maybe waits until the connection closes?
  {
    while (client.available())
    {
      timeout = millis();
    }
  }
 
  // Shutdown
  http.stop();
  client.stop();
  modem.gprsDisconnect();
      }
 
    }
    set.DB=true;
    set.sensor_count=0;
    set.cloud="";
    set.fulldata="";
}

void AddData(String id, String header, String data){
  if(set.DB==false){
  if(set.date.unixtime()==1702511185){
    set.firstMillis=set.previousMillis+set.timeInterval;
  }
  set.sensor_count++;
  set.fulldata+=header+set.seperate;
  set.cloud+="logb"+String(set.sensor_count)+"="+header+"&sensor"+String(set.sensor_count)+"="+id+"&";
  }else{
  set.sensor_count++;
  set.fulldata+=data;
  set.fulldata+=set.seperate;
  set.cloud+="logb"+String(set.sensor_count)+"="+data+"&";
  }
}
