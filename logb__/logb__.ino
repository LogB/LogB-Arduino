#include "logb.h"

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
WiFi.begin("Potyka", "62Botticelli2016");
while (WiFi.status() != WL_CONNECTED) {delay(50);}
set.device_id="cimbi21_1";
set.pin="admin";
set.where="a";
set.timeInterval=2000;

CreateName(UnixTime(1));
Serial.println(set.file);
AddNewHeaderParam("SHT21-I2C-3V3-TEMP-C", "Temperature");
AddNewHeaderParam("SHT21-I2C-3V3-HUM-%", "Humidity");
//("BH1750-I2C-3V3-LIGHT-lx", "Light");
Send();
}

void loop() {
set.currentMillis = millis(); 
if (set.currentMillis - set.previousMillis >= set.timeInterval) { 
set.previousMillis = set.currentMillis; 
Time(UnixTime(1));
AddNewSensorData("SHT21-I2C-3V3-TEMP-C", String(SHT2x.GetTemperature()));
AddNewSensorData("SHT21-I2C-3V3-HUM-%", String(SHT2x.GetHumidity()));
//AddNewSensorData("BH1750-I2C-3V3-LIGHT-lx", String(lightMeter.readLightLevel()));
Send();
}
}
