#include "src/Button.h"
#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C display(0x27, 20, 4);

#define BUTTON_COUNT 6
Button btnLeft(30);
Button btnRight(31);
Button btnUp(32);
Button btnDown(33);
Button btnSubmit(34);
Button btnCancel(35);

Button* btns[BUTTON_COUNT]
{
  &btnLeft,
  &btnRight,
  &btnUp,
  &btnDown,
  &btnSubmit,
  &btnCancel
};

float temp;
float humidity;

void openGUIScreen(int index);
void drawGUIFooter();
void drawSensorGUI();

#define GUI_SCREEN_COUNT 3
int currentGUI = 0;
void(*GUIScreens[GUI_SCREEN_COUNT])() =
{
  drawSensorGUI,
  drawSensorGUI,
  drawSensorGUI
};

void setup()
{
  display.begin();
  dht.begin();

  for (int i = 0; i < BUTTON_COUNT; ++i)
  {
    btns[i]->begin();
  }

  openGUIScreen(0);
}

void loop()
{
  temp = dht.readTemperature();
  humidity = dht.readHumidity();

  for (int i = 0; i < BUTTON_COUNT; ++i)
  {
    btns[i]->update();
  }

  if (btnLeft.isDownNow()) { openGUIScreen(currentGUI - 1); }
  else if (btnRight.isDownNow()) { openGUIScreen(currentGUI + 1); }

  GUIScreens[currentGUI]();
}

void openGUIScreen(int index)
{
  if (index >= GUI_SCREEN_COUNT) { index = GUI_SCREEN_COUNT - 1; }
  if (index < 0) { index = 0; }
  currentGUI = index;
  drawGUIFooter();
}

void drawGUIFooter()
{
  display.setCursor(0, 3);
  display.print(currentGUI + 1);
  display.print('/');
  display.print(GUI_SCREEN_COUNT);
}

void drawSensorGUI()
{
  display.setCursor(0, 0);
  display.print("Temperature: ");
  display.print((int)temp);
  display.print("C   ");
  
  display.setCursor(0, 1);
  display.print("Humidity: ");
  display.print((int)humidity);
  display.print("%   ");
}
