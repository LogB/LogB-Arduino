#include "logb.h"
 unsigned long previousMillis = 0;
  //unsigned long timeInterval= 1000;
  unsigned long currentMillis=0;
//#include "DS3231.h"
Settings set;
BH1750 lightMeter;
RTC_DS3231 rtc;
void setup() {
  Serial.begin(115200);
      
   
    
Wire.begin();
//lightMeter.begin();
rtc.begin();
//WiFi.begin("LogB Cloud", "logb2018");
//WiFi.begin("Potyka", "62Botticelli2016");
//while (WiFi.status() != WL_CONNECTED) {delay(50);}
set.device_id="cimbi21_1";
set.pin="admin";
set.where="ab";
//set.timeInterval=2000;

CreateName(rtc.now());
AddNewHeaderParam(1, "Temperature");
AddNewHeaderParam(2, "Humidity");

Send();
}

void loop() {
currentMillis = millis(); 
if (currentMillis - previousMillis >= 2000) { 
previousMillis = currentMillis; 
set.date=rtc.now();
AddNewSensorData(1, String(SHT2x.GetTemperature()));
AddNewSensorData(2, String(SHT2x.GetHumidity()));
Serial.println(rtc.now().unixtime());
//AddNewSensorData("BH1750-I2C-3V3-LIGHT-lx", String(lightMeter.readLightLevel()));

Send();
}
}
