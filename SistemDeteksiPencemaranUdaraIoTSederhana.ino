#include "LiquidCrystal_I2C.h"
#include <Wire.h>
#include <RTClib.h>
#include <TM1637Display.h>
#include <dht.h>
#define dataPin 10 // Defines pin number to which the sensor is connected
dht DHT; // Creats a DHT object
#define MQ2pin 12
#include "MQ7.h"
MQ7 mq7(A1,5.0);

int redLed = 2;  // LED dihubungkan dengan pin 12 Arduino
int buzzer = 11;  // Buzzer dihubungkan dengan pin 10 Arduino 
int sensorThres = 4; // Tegangan threshold Sensor yg kita inginkan
int sensorValue2;

#define CLK 8
#define DIO 9
RTC_DS3231 rtc;
TM1637Display display = TM1637Display(CLK, DIO);

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  pinMode(redLed, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.println("MQ2 warming up!");
	delay(20000);

    if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
 
  if (rtc.lostPower()) {
    //Serial.println("RTC lost power, lets set the time!");
    
    //rtc.adjust(DateTime());
 
  }

  // Set the display brightness (0-7):
  display.setBrightness(5);
  // Clear the display:
  display.clear();

}

void loop() {
//MQ-7
  float ppmValue = mq7.getPPM(); // Mendapatkan nilai PPM dari sensor MQ7
    if (ppmValue > 10) {
        digitalWrite(redLed, HIGH); // Menyalakan LED jika nilai PPM lebih besar dari 5.0
    } else {
        digitalWrite(redLed, LOW); // Mematikan LED jika nilai PPM kurang dari atau sama dengan 5.0
    }
    
  lcd.setCursor(0, 0);
  lcd.print("CO MONOXIDE: ");
  lcd.print(ppmValue);
  lcd.print(" P");



 //MQ-2
  sensorValue2 = digitalRead(MQ2pin);

  if (sensorValue2) {
    digitalWrite(buzzer, LOW);
    lcd.setCursor(0, 3);
    lcd.print("                  ");
    
	} else {
    digitalWrite(buzzer, HIGH);
    lcd.setCursor(0, 3);
    lcd.print("Polusi Asap/Kabut!");
    
	}


   DateTime now = rtc.now();


  int displaytime = (now.hour() * 100) + now.minute();


  display.showNumberDecEx(displaytime, 0b11100000, true);


  display.showNumberDec(displaytime, true);

	int readData = DHT.read22(dataPin); 

	float t = DHT.temperature;
	float h = DHT.humidity;



  lcd.setCursor(0, 1);
  lcd.print("Suhu       : ");
  lcd.print(t);
  lcd.print("C");

  lcd.setCursor(0, 2);
  lcd.print("Kelembaban : ");
  lcd.print(h);
  lcd.print("%");


kirim();

}

void kirim() {
  float t = DHT.temperature; 
	float h = DHT.humidity;
  int h1 = h;
  int t1 = t;
  int sensorValue = analogRead(A1);
  String strsuhu = String(h1);
  String strhum = String(t1);
  String strsv = String (sensorValue);
  Serial.println('*' + strhum + ',' + strsuhu + ',' + strsv + '#');
}