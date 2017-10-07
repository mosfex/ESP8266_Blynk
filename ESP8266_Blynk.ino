/*
* Written by Mosfex : www.mosfex.com
* www.fb.com/mosfex 
* plese refer to this when using the code
*/
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "...";        //Blynk auth token
char ssid[] = "mosfex.com"; //WiFi SSID
char pass[] = "123456789";  //WiFi password

#define DHTPIN D4

#define DHTTYPE DHT11
//#define DHTTYPE DHT22// DHT 22, AM2302, AM2321

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
}
void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}

void loop() {  
  Blynk.run();
  timer.run();
}