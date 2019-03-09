//logb.cpp
#include "logb.h"

#if defined(ESP8266)
HTTPClient http; 
#endif

time_t UnixTime(int tz){
  #if defined(ESP8266)
  time_t now=0;
  String date="";
  int timezone = tz * 3600;
  int dst = 0;
  while(now<958881900){
  configTime(timezone, dst, "pool.ntp.org","time.nist.gov");
  while(!time(nullptr)){
    delay(200);
  }delay(100);
now = time(nullptr);
  }
return now;
#endif
}

void CreateName(time_t time){
  set.ArduinoName=set.device_id+"_"+String(time);
  Time(time);
}

void Time(time_t time){
 struct tm* p_tm = localtime(&time);
 char number="0123456789"
 String date;
 String d;
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
set.date= date;
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

void Send(){
  String fulldata;
  if(set.DB==false){
#if defined(ESP8266)
http.begin("http://cloud.logb.hu/cloud/upload.php");
http.addHeader("Content-Type", "application/x-www-form-urlencoded");
String post="oszlop="+String(set.sensor_count)+"&ma="+set.ArduinoName+"&pin="+set.pin+"&device="+set.device_id+"&time="+set.date;
        for(int i=0;i<set.sensor_count;i++){
        post+="&logb"+String(i+1)+"="+set.header[i];
        post+="&sensor"+String(i+1)+"="+set.sensors[i];
        }
int httpCode=http.POST(post);
//Serial.println(httpCode);
#endif

for(int i=0;i<set.sensor_count;i++){
  set.store[i]=set.header[i];
}
set.DB=true;
fulldata="Date";
  }else{
    fulldata=set.date;
  }
    for (int j = 0; j < set.where.length(); j++){
    char w = set.where.charAt(j);
    fulldata+=set.semicolon;
     for(int i=0;i<set.sensor_count;i++){
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
    }if(w=='c' and set.DB){
        #if defined(ESP8266)
         String post="oszlop="+String(set.sensor_count)+"&ma="+set.ArduinoName+"&pin="+set.pin+"&device="+set.device_id+"&time="+set.date;
        for(int i=0;i<set.sensor_count;i++){
        post+="&logb"+String(i+1)+"="+set.store[i];
      }
        int httpCode=http.POST(post);
        //Serial.println(httpCode);
         #endif
    }
 
    }
}
void AddNewSensorData(String id, String data){
  int sensorID=-1;
  for (int i=0;i<set.sensor_count ;i++){
    if(set.sensors[i]==id){
      sensorID=i;
    }
  }
  if(sensorID>-1){
   set.store[sensorID]=data;
  }
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

void AddNewHeaderParam(String id, String header){
  set.sensors[set.sensor_count]=id;
  set.header[set.sensor_count]=header;
  set.sensor_count++;
  //set.now++;
}
