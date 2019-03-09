#include "logb.h"
#include "Sodaq_SHT2x.h"
#include "BH1750.h"
Settings set;
BH1750 lightMeter;

void setup() {
Serial.begin(115200); 
Wire.begin();
lightMeter.begin();
//WiFi.begin("LogB Cloud", "logb2018");
WiFi.begin("Potyka", "62Botticelli2016");
//delay(5000);//ki kell venni
set.device_id="cimbi21_1";
set.pin="admin";
set.where="ac";
set.timeInterval=2000;
CreateName(UnixTime(1));
AddNewHeaderParam("SHT21-I2C-3V3-TEMP-C", "Temperature");
AddNewHeaderParam("SHT21-I2C-3V3-HUM-%", "Humidity");
AddNewHeaderParam("BH1750-I2C-3V3-LIGHT-lx", "Light");
Send();
}

void loop() {
set.currentMillis = millis(); 
if (set.currentMillis - set.previousMillis >= set.timeInterval) { 
set.previousMillis = set.currentMillis; 
Time(UnixTime(1));
AddNewSensorData("SHT21-I2C-3V3-TEMP-C", String(SHT2x.GetTemperature()));
AddNewSensorData("SHT21-I2C-3V3-HUM-%", String(SHT2x.GetHumidity()));
AddNewSensorData("BH1750-I2C-3V3-LIGHT-lx", String(lightMeter.readLightLevel()));
Send();
}
}
