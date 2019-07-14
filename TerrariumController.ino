#include "src/Button.h"
#include "src/SensorsModule.h"
#include "src/OutputsModule.h"
#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHT_PIN 2
#define LED_PIN 3

LiquidCrystal_I2C display(0x27, 20, 4);

#define BUTTON_COUNT 6
Button btnLeft(30);
Button btnRight(31);
Button btnUp(32);
Button btnDown(33);
Button btnCancel(34);
Button btnSubmit(35);

Button* btns[BUTTON_COUNT]
{
  &btnLeft,
  &btnRight,
  &btnUp,
  &btnDown,
  &btnSubmit,
  &btnCancel
};

int vcursor = 0;

int time = 0;
int lastTime = 0;
int deltaTime = 0;

void openGUIScreen(int index);
void drawGUIFooter();

#define MODULE_COUNT 2
SensorsModule sensorsModule(DHT_PIN);
OutputsModule outputsModule(LED_PIN);
int currentlyDisplayedModule = 0;
Module* modules[MODULE_COUNT]
{
  &sensorsModule,
  &outputsModule
};

void setup()
{
  display.begin();

  for (int i = 0; i < MODULE_COUNT; ++i)
  {
    modules[i]->begin();
  }

  for (int i = 0; i < BUTTON_COUNT; ++i)
  {
    btns[i]->begin();
  }

  time = millis();
  lastTime = millis();
  deltaTime = 0;

  openGUIScreen(0);
}

void loop()
{
  for (int i = 0; i < BUTTON_COUNT; ++i)
  {
    btns[i]->update();
  }

  for (int i = 0; i < MODULE_COUNT; ++i)
  {
    modules[i]->update();
  }

  lastTime = time;
  time = millis();
  deltaTime = time - lastTime;

  if (btnLeft.isDownNow()) { openGUIScreen(currentlyDisplayedModule - 1); }
  else if (btnRight.isDownNow()) { openGUIScreen(currentlyDisplayedModule + 1); }

  modules[currentlyDisplayedModule]->drawGUI(display);
}

void openGUIScreen(int index)
{
  if (index >= MODULE_COUNT) { index = MODULE_COUNT - 1; }
  if (index < 0) { index = 0; }
  currentlyDisplayedModule = index;
  display.clear();
  drawGUIFooter();
}

void drawGUIFooter()
{
  display.setCursor(0, 3);
  display.print(currentlyDisplayedModule + 1);
  display.print('/');
  display.print(MODULE_COUNT);
  display.print(' ');
  display.print(modules[currentlyDisplayedModule]->getName());
}
