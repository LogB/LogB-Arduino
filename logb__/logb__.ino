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
set.where="ab";
set.timeIntervall=2000;
CreateName(rtc.now());
}
void loop() {
set.currentMillis = millis(); 
if (set.currentMillis - set.previousMillis >= set.timeIntervall) { 
set.previousMillis = set.currentMillis; 
AddData("Date",   Time(NoTime()));
AddData("Temp",  String(SHT2x.GetHumidity()));
AddData("Hum",   String(SHT2x.GetTemperature()));
Send();
}
}
