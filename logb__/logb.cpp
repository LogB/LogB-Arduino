//logb.cpp
#include "logb.h"

#if defined(ESP8266)
HTTPClient http; 
#endif

void connectToDB(){
#if defined(ESP8266)
http.begin("http://cloud.logb.hu/cloud/upload.php");             
http.addHeader("Content-Type", "application/x-www-form-urlencoded");
#endif
}

String TableName(int tz){
  #if defined(ESP8266)
  String date="";
  int timezone = tz * 3600;
  int dst = 0;
  configTime(timezone, dst, "pool.ntp.org","time.nist.gov");
  while(!time(nullptr)){
    delay(2000);
  }delay(4000);
date = time(nullptr);
return date;
#endif
}

String onlineDate(int tz){
  #if defined(ESP8266)
  String date="";
  int timezone = tz * 3600;
  int dst = 0;
  String d;
  String n="0";
  configTime(timezone, dst, "pool.ntp.org","time.nist.gov");

  while(!time(nullptr)){
    delay(1000);
  } 
time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
 
  date+=p_tm->tm_year + 1900;  
  date+="-";
  d=p_tm->tm_mon + 1;
   if(d=="0" or d=="1" or d=="2" or d=="3" or d=="4" or d=="5" or d=="6" or d=="7" or d=="8" or d=="9"){
     date+=n;
     date+=d;
   }else{
    date+=d;
   }
  date+="-";
  d= p_tm->tm_mday;
  if(d=="0" or d=="1" or d=="2" or d=="3" or d=="4" or d=="5" or d=="6" or d=="7" or d=="8" or d=="9"){
     date+=n;
     date+=d;
   }else{
    date+=d;
   }
  date+=" ";
  d=p_tm->tm_hour;
  if(d=="0" or d=="1" or d=="2" or d=="3" or d=="4" or d=="5" or d=="6" or d=="7" or d=="8" or d=="9"){
     date+=n;
     date+=d;
   }else{
    date+=d;
   }
  date+=":";
  d=p_tm->tm_min;
  if(d=="0" or d=="1" or d=="2" or d=="3" or d=="4" or d=="5" or d=="6" or d=="7" or d=="8" or d=="9"){
     date+=n;
     date+=d;
   }else{
    date+=d;
   }
  date+=":";
  d=p_tm->tm_sec;
  if(d=="0" or d=="1" or d=="2" or d=="3" or d=="4" or d=="5" or d=="6" or d=="7" or d=="8" or d=="9"){
     date+=n;
     date+=d;
   }else{
    date+=d;
   }
return date;
 #endif
}

/*
String fileNameCreate(){
  String file;
  DateTime now = rtc.now();
  file="";
  file+=now.month();
  file+=now.day();
  file+=now.hour();
  file+=now.minute();
  file+=".txt";
  return file;
}
/*
String Date(){
  String date="";
  DateTime now = rtc.now();
    date= now.year();
    date+="/";
    date+=now.month();
    date+="/";
    date+=now.day();
    return date;
}
String Time(){
  String t="";
  DateTime now = rtc.now();
    t+=now.hour();
    t+=":";
    t+=now.minute();
    t+=":";
    t+=now.second();
    return t;
}

String GPSread(){
  char data;
  String full="";
  int gps=1;
  Wire.requestFrom(8,19);
 while(Wire.available()and gps<20){
  data = Wire.read();
  full+=data;
  gps++;
}
return full;
}
/*
void dateTime(uint16_t* date, uint16_t* time) {
  DateTime now = rtc.now();
  *date = FAT_DATE(now.year(), now.month(), now.day());
  *time = FAT_TIME(now.hour(), now.minute(), now.second());
}*/

/*void timeSetting(){
 if(rtc.lostPower())
 {
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
 }
}
*/

void out(String data){
  set.store[set.now]=data;
   if(set.now==set.db){
    for (int j = 0; j < set.where.length(); j++){
    char w = set.where.charAt(j);
    String fulldata="";
     for(int i=1;i<=set.db;i++){
      String d=set.store[i];
        if(set.toComma){
         
          d.replace('.',',');
        }
        fulldata+=d;
        fulldata+=set.semicolon;
      }
    if (w=='a'){
   Serial.println(fulldata);
    }

    if (w=='b'){
      SdFat SD;
      //SdFile::dateTimeCallback(dateTime);
      File Sd = SD.open(set.file, FILE_WRITE);
        if(Sd){
          Sd.println(fulldata);
        }
        Sd.close();
    }if(w=='c'){
        #if defined(ESP8266)
         String post="oszlop="+String(set.db)+"&date="+set.date+"&pin="+set.pin+"&device="+set.device+"&time="+String(onlineDate(1));
        for(int i=1;i<=set.db;i++){
        post+="&logb"+String(i)+"="+set.store[i];
      }
        int httpCode=http.POST(post);
         #endif
    }
 
    }set.now=0;
  }set.now++;
}
String DIPconfig(){
  String b="";
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  pinMode(14,INPUT_PULLUP);
  pinMode(15,INPUT_PULLUP);

  b+=String(digitalRead(3));
  b+=String(digitalRead(4));
  b+=String(digitalRead(5));
  b+=String(digitalRead(15));
  b+=String(digitalRead(14));
  b+=String(digitalRead(6));
  b+=String(digitalRead(7));
  b+=String(digitalRead(8));
  b+=String(digitalRead(9));
  b+=String(digitalRead(10));
  
  return b;
}

long int interval(String b){
  long int timeinterval=0;
  for (int i=0;i<10;i++){
    String n= String(b.charAt(i));
    int nt=n.toInt();
    int exponent[10]={1,2,4,8,16,32,64,128,256,512};
    timeinterval+= nt*exponent[i];
  }
  timeinterval*=1000;
  return timeinterval;
}
