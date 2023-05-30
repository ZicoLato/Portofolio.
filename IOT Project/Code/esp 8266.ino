#define BLYNK_TEMPLATE_ID "TMPLKJmaz-ag"
#define BLYNK_DEVICE_NAME "Greenhouse"
#define BLYNK_AUTH_TOKEN "Tec_EvouZ-qgP3wt0iwhgI5ZNZZQ-iY2"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>


char auth[] = "Tec_EvouZ-qgP3wt0iwhgI5ZNZZQ-iY2";

char ssid[] = "Rexus";  //Enter your WIFI Name
char pass[] = "#Nitro#099$$";  //Enter your WIFI Password

#define DHTPIN D5          // Mention the digital pin where you connected 
#define DHTTYPE DHT22      
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
float h;
float t;




void setup(){
  Serial.begin(9600); 
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  dht.begin();
  timer.setInterval(2500, sendSensor);
}

void loop(){
  
  h = dht.readHumidity()-20;
  t = dht.readTemperature();
  Blynk.run();
  timer.run();

  delay(2000);
  Serial.print("Suhu : ");
  Serial.print(t);
  Serial.print("|| Kelembapan : ");
  Serial.println(h);
}

void sendSensor(){
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);

}
