#include "src/Button.h"
#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C display(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

Button btnLeft(3);
Button btnRight(4);

float temp;
float humidity;

void drawSensorGUI();

int currentGUI = 0;
void(*GUIScreens[]) =
{
  drawSensorGUI
};

void setup()
{
  display.begin(20, 4);
  dht.begin();
}

void loop()
{
  temp = dht.readTemperature();
  humidity = dht.readHumidity();

  GUIScreens[currentGUI]();
  delay(1000);
}

void drawSensorGUI()
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
