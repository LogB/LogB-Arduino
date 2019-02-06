#include "logb.h"
#include "Sodaq_SHT2x.h"
Settings set;
void setup() {
Serial.begin(115200); 
Wire.begin();
WiFi.begin("LogB Cloud", "logb2018");
delay(1500);
connectToDB();
set.device="cimbi21_1";
set.pin="admin";
set.date = TableName(1);
set.db=3;
set.where="ac";
set.timeInterval=5000;
out("Temperature");
out("Humidity");
out("DewPoint");
}
void loop() {
set.currentMillis = millis(); 
if (set.currentMillis - set.previousMillis >= set.timeInterval) { 
set.previousMillis = set.currentMillis; 
//out(onlineDate(1));
out(String(SHT2x.GetTemperature()));
out(String(SHT2x.GetHumidity()));
out(String(SHT2x.GetDewPoint()));


}
}
