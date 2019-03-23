#include "logb.h"
#include "BH1750.h"
#include "Sodaq_SHT2x.h"
#include "Adafruit_BMP085.h"
Settings set;
BH1750 lightMeter;
RTC_DS1307 rtc;
Adafruit_BMP085 bmp;
void setup() {
Serial.begin(115200);
Wire.begin();
lightMeter.begin();
bmp.begin();
rtc.begin();
if(rtc.lostPower()){rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));}
WiFi.begin("LogB Cloud", "logb2018");
while (WiFi.status() != WL_CONNECTED) {delay(50);}
set.device_id="cimbi21_1";
set.pin="admin";
set.where="a";
set.timeInterval=500;
CreateName(rtc.now());
}
void loop() {
set.currentMillis = millis(); 
if (set.currentMillis - set.previousMillis >= set.timeInterval) { 
set.previousMillis = set.currentMillis; 
AddData("DS1307-RTC","Date",   Time(rtc.now()));
AddData("SHT21-TEMP","Temperature",   String(SHT2x.GetTemperature()));
AddData("SHT21-HUM","Humidity",  String(SHT2x.GetHumidity()));
AddData("BMP180-PRES","Pressure",  String(bmp.readPressure()));
AddData("BH1750-Light","Light",  String(lightMeter.readLightLevel()));
Send();
}
}
