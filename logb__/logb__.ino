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
WiFi.begin("Potyka", "62Botticelli2016");
while (WiFi.status() != WL_CONNECTED) {delay(50);}
set.device_id="cimbi21_1";
set.pin="admin";
set.where="a";
set.timeIntervall=500;
//CreateName(UnixTime(1));
}
void loop() {
set.currentMillis = millis(); 
if (set.currentMillis - set.previousMillis >= set.timeIntervall) { 
set.previousMillis = set.currentMillis; 
AddData("NTP","Date",   Time(NoTime()));
AddData("SHT21","Temp",  String(SHT2x.GetHumidity()));
AddData("SHT21","Hum",   String(SHT2x.GetTemperature()));
Send();
}
}
