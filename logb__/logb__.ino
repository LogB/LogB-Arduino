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
AddNewHeaderParam(3, "Humidity");
AddNewHeaderParam(4, "Humidity");
AddNewHeaderParam(5, "Humidity");
AddNewHeaderParam(6, "Humidity");
AddNewHeaderParam(7, "Humidity");
AddNewHeaderParam(8, "Humidity");
AddNewHeaderParam(9, "Humidity");
AddNewHeaderParam(10, "Humidity");
//("BH1750-I2C-3V3-LIGHT-lx", "Light");

Send();
}

void loop() {
currentMillis = millis(); 
if (currentMillis - previousMillis >= 2000) { 
previousMillis = currentMillis; 
Time(rtc.now());
AddNewSensorData(1, String(SHT2x.GetTemperature()));
AddNewSensorData(2, String(SHT2x.GetHumidity()));
AddNewSensorData(3, String(SHT2x.GetTemperature()));
AddNewSensorData(4, String(SHT2x.GetTemperature()));
AddNewSensorData(5, String(SHT2x.GetTemperature()));
AddNewSensorData(6, String(SHT2x.GetTemperature()));
AddNewSensorData(7, String(SHT2x.GetTemperature()));
AddNewSensorData(8, String(SHT2x.GetTemperature()));
AddNewSensorData(9, String(SHT2x.GetTemperature()));
AddNewSensorData(10, "Humidity");
//AddNewSensorData("BH1750-I2C-3V3-LIGHT-lx", String(lightMeter.readLightLevel()));

Send();
}
}
