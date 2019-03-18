#include "logb.h"
#include "BH1750.h"
#include "Sodaq_SHT2x.h"
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
CreateName(rtc.now());
AddNewHeaderParam(1, "Temperature");
AddNewHeaderParam(2, "Humidity");
Send();
}
void loop() {
set.currentMillis = millis(); 
if (set.currentMillis - set.previousMillis >= 2000) { 
set.previousMillis = set.currentMillis; 
set.date=rtc.now();
AddNewSensorData("Temperature",   String(SHT2x.GetTemperature()));
AddNewSensorData("2Temperature",  String(SHT2x.GetHumidity()));
AddNewSensorData("2Temperature",  String(SHT2x.GetHumidity()));
AddNewSensorData("2Tsemperature", String(SHT2x.GetHumidity()));
AddNewSensorData("2Tesmperature", String(SHT2x.GetHumidity()));
AddNewSensorData("2Temsperature", String(SHT2x.GetHumidity()));
AddNewSensorData("2Tempearature", String(SHT2x.GetHumidity()));
AddNewSensorData("2Temperaature", String(SHT2x.GetHumidity()));
AddNewSensorData("2Tempercature", String(SHT2x.GetHumidity()));
AddNewSensorData("2Temperaíture", String(SHT2x.GetHumidity()));
Send();
}
}
