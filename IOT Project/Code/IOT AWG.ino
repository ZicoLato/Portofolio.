
#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 

#define dht_pin 2
#define led_merah 9
#define led_kuning 10
#define led_biru 11
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define DHTTYPE DHT22
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DHT dht(dht_pin, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);


void setup(){
Serial.begin(115200);
dht.begin();
lcd.init();
Serial.begin(9600);
dht.begin();
lcd.backlight();
lcd.setBacklight(HIGH);
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.clearDisplay();
pinMode(led_merah, OUTPUT);
pinMode(led_kuning, OUTPUT);
pinMode(led_biru, OUTPUT);

}

void loop(){

delay(2000);
  
float h = dht.readHumidity()-20;
float suhu = dht.readTemperature();
float f = dht.readTemperature(true);

lcd.setCursor(0,0);
lcd.print("Humi : ");
lcd.print(h);
lcd.print(" %");
lcd.setCursor(0,1);
lcd.print("Temp : "); 
lcd.print(suhu);
lcd.println(" C     ");
   
    Serial.print(" Humidity: ");
    Serial.print(h);
    Serial.print(" %, Temp: ");
    Serial.print(suhu);
    Serial.println(" Celsius");
    delay(10000);   
  
delay(2000);
display.setFont(&FreeSerif9pt7b);
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0, 40);



if (isnan (h) || isnan (suhu) || isnan (f)) {
  return;

}

float hif = dht.computeHeatIndex(f,h);
float hic = dht.computeHeatIndex(suhu,h, false);

if (suhu <29) {
  digitalWrite(led_merah, HIGH);
  digitalWrite(led_kuning, HIGH);
  digitalWrite(led_biru, HIGH);
}

else if (suhu <=35 and suhu >=29){
  digitalWrite(led_merah, HIGH);
  digitalWrite(led_kuning, HIGH);
  digitalWrite(led_biru, LOW);
}
else if (suhu >35){
  digitalWrite(led_merah, HIGH);
  digitalWrite(led_kuning, LOW);
  digitalWrite(led_biru, LOW);
}
else if (suhu >38){
  digitalWrite(led_merah, LOW);
  digitalWrite(led_kuning, LOW);
  digitalWrite(led_biru, LOW);
}

else {
  digitalWrite(led_merah, LOW);
  digitalWrite(led_kuning, LOW);
  digitalWrite(led_biru, LOW);
  }
}
