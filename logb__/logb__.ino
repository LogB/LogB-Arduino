#include "logb.h"
#include "Sodaq_SHT2x.h"

Settings set;
void setup() {
Serial.begin(115200); 
Wire.begin();
//WiFi.begin("LogB Cloud", "logb2018");
WiFi.begin("Potyka", "62Botticelli2016");
delay(5000);
set.device_id="cimbi21_1";
set.pin="admin";
set.where="ac";
set.timeInterval=40000;
CreateName(UnixTime(1));
AddNewHeaderParam("SHT21-I2C-3V3-TEMP-C", "Temperature");
AddNewHeaderParam("SHT21-I2C-3V3-HUM-%", "Humidity");
Send();

}
void loop() {
set.currentMillis = millis(); 
if (set.currentMillis - set.previousMillis >= set.timeInterval) { 
set.previousMillis = set.currentMillis; 
Time(UnixTime(1));
AddNewSensorData("SHT21-I2C-3V3-TEMP-C", String(SHT2x.GetTemperature()));
AddNewSensorData("SHT21-I2C-3V3-HUM-%", String(SHT2x.GetHumidity()));
Send();
}
}
