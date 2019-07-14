#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C display(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup()
{
  display.begin(20, 4);
  dht.begin();
}

void loop()
{
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  drawSensorGUI(temp, humidity);
  delay(1000);
}

void drawSensorGUI(float temp, float humidity)
{
  display.setCursor(0,0);
  display.print("Temperature: ");
  display.print((int)temp);
  display.print("  ");
  
  display.setCursor(0,1);
  display.print("Humidity: ");
  display.print((int)humidity);
  display.print("  ");
}

