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
  set.date=time;
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
String fulldata;

if(set.DB==false){
fulldata="Date";
}
else{
    fulldata=Time(set.date);
  }
    for (int j = 0; j < set.where.length(); j++){
      char w = set.where.charAt(j);
      fulldata+=set.seperate;
      for(int i=0;i<set.sensor_count;i++){
        String d=set.store[i];
          if(set.toComma){
            d.replace('.',',');
           }   
          fulldata+=d;
          fulldata+=set.seperate;
      }
      
  if (w=='a'){
  Serial.println(fulldata);
    }

  if (w=='b'){
  SdFile::dateTimeCallback(dateTime);
      if(set.DB==false){
      SD.begin(SS);
      }
      String file=set.ArduinoName+".txt";
      File Sd = SD.open(file, FILE_WRITE);
        if(Sd){
          Sd.println(fulldata);
        }
        Sd.close();
    }
    
  if(w=='c'){
       #if defined(ESP8266)
        String post;
        http.begin("http://api.logb.hu/v1/upload.php");
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        if(set.DB){
          post="oszlop="+String(set.sensor_count)+"&ma="+set.ArduinoName+"&pin="+set.pin+"&device="+set.device_id+"&time="+Time(set.date);
          for(int i=0;i<set.sensor_count;i++){
            post+="&logb"+String(i+1)+"="+set.store[i];
          }
        }
          else{
          post="oszlop="+String(set.sensor_count)+"&ma="+set.ArduinoName+"&pin="+set.pin+"&device="+set.device_id+"&time="+Time(set.date);
          for(int i=0;i<set.sensor_count;i++){
            post+="&logb"+String(i+1)+"="+set.header[i];
            post+="&sensor"+String(i+1)+"="+set.sensors[i];
          }
        }
        int httpCode=http.POST(post);
        http.end();
        //Serial.println(httpCode);
       #endif
    }
 
    }
    set.DB=true;
}

void AddNewSensorData(int id, String data){
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

void AddNewHeaderParam(int id, String header){
  set.sensors[set.sensor_count]=id;
  set.store[set.sensor_count]=header;
  set.sensor_count++;
}
