//logb.cpp
#include "logb.h"
SdFat SD;

#if defined(ESP8266)
HTTPClient http; 
#endif

DateTime UnixTime(int tz){
  #if defined(ESP8266)
  time_t now=0;
  String date="";
  int timezone = tz * 3600;
  int dst = 0;
  while(now<958881900){
  configTime(timezone, dst, "pool.ntp.org","time.nist.gov");
  while(!time(nullptr)){
  }delay(10);
now = time(nullptr);
  }
return now;
#endif
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
  set.date=time;
 String date;
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
return date;
}

void dateTime(uint16_t* date, uint16_t* time) {
  DateTime now = set.date;
  *date = FAT_DATE(now.year(), now.month(), now.day());
  *time = FAT_TIME(now.hour(), now.minute(), now.second());
}

void Send(){
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
            http.begin("http://api.logb.hu/v1/upload.php");
            http.addHeader("Content-Type", "application/x-www-form-urlencoded");
            set.cloud+="oszlop="+String(set.sensor_count)+"&ma="+set.ArduinoName+"&pin="+set.pin+"&device="+set.device_id+"&time="+Time(set.date);
            int httpCode=http.POST(set.cloud);
            http.end();
            //Serial.println(httpCode);
           #endif
        }
 
    }
    set.DB=true;
    set.sensor_count=0;
    set.cloud="";
    set.fulldata="";
}

void AddData(String id, String data){
  if(set.DB==false){
  set.sensor_count++;
  set.fulldata+=id+set.seperate;
  set.cloud+="l"+String(set.sensor_count)+id+"&";
  }else{
  set.sensor_count++;
  set.fulldata+=data;
  set.fulldata+=set.seperate;
  set.cloud+="l"+String(set.sensor_count)+data+"&";
  }
}
