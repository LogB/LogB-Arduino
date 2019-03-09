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
String wz(int n){
  String r="0";
  if(n<10){
    r+=n;
  }else{
    r=n;
  }return r;
}
void Time(time_t time){
 struct tm* p_tm = localtime(&time);
 String date;
  date+=p_tm->tm_year + 1900;  
  date+="-";
  date+=wz(p_tm->tm_mon + 1);
  date+="-";
  date+=wz(p_tm->tm_mday);
  date+=" ";
  date+=wz(p_tm->tm_hour);
  date+=":";
  date+=wz(p_tm->tm_min);
  date+=":";
  date+=wz(p_tm->tm_sec);
set.date= date;
}

void Send(){
  String fulldata;
  if(set.DB==false){
#if defined(ESP8266)//ha cloudra kimaradt
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

void AddNewHeaderParam(String id, String header){
  set.sensors[set.sensor_count]=id;
  set.header[set.sensor_count]=header;
  set.sensor_count++;
  //set.now++;
}
