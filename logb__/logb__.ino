#include "logb.h"
#include "BH1750.h"
#include "Sodaq_SHT2x.h"
#include "Adafruit_BMP085.h"
Settings set;
BH1750 lightMeter;
//RTC_DS1307 rtc;
Adafruit_BMP085 bmp;
void setup() {
Serial.begin(115200);
Wire.begin();
lightMeter.begin();
bmp.begin();
//rtc.begin();
//if(!rtc.isrunning()){rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));}
WiFi.begin("LogB", "logb2018");
while (WiFi.status() != WL_CONNECTED) {delay(100); Serial.print(".");}
set.device_id="cimbi21_1";
set.pin="admin";
set.where="abc";
set.timeInterval=2000;
CreateName(UnixTime(1));
}
void loop() {
set.currentMillis = millis(); 
if (set.currentMillis - set.previousMillis >= set.timeInterval) { 
set.previousMillis = set.currentMillis; 
AddData("NTP-RTC","Date",   Time(UnixTime(1)));
AddData("SHT21-TEMP","Hőmérséklet",   String(SHT2x.GetTemperature()));
AddData("SHT21-HUM","Páratartalom",  String(SHT2x.GetHumidity()));
AddData("BMP180-PRES","Nyomás",  String(bmp.readPressure()));
AddData("BH1750-LIGHT","Fény",  String(lightMeter.readLightLevel()));
Send();
}
}
