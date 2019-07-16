#include "src/Button.h"
#include "src/ControlPackage.h"
#include "src/SensorsModule.h"
#include "src/OutputsModule.h"
#include "src/LoggingModule.h"
#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

ControlPackage pkg;

#define DHT_PIN 2
#define LED_PIN 3
#define FAN_PIN 4

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

int time = 0;
int lastTime = 0;

void openGUIScreen(int index);
void drawGUIFooter();
void drawGUIvCursor();

#define MODULE_COUNT 3
SensorsModule sensorsModule(DHT_PIN);
OutputsModule outputsModule(LED_PIN, FAN_PIN);
LoggingModule loggingModule(sensorsModule, outputsModule);
int currentlyDisplayedModule = 0;
Module* modules[MODULE_COUNT]
{
  &sensorsModule,
  &outputsModule,
  &loggingModule
};

void setup()
{
  pkg.btnSubmit = &btnSubmit;
  pkg.btnCancel = &btnCancel;

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
  pkg.deltaTime = 0;

  openGUIScreen(0);
}

void loop()
{
  lastTime = time;
  time = millis();
  pkg.deltaTime = time - lastTime;

  for (int i = 0; i < BUTTON_COUNT; ++i)
  {
    btns[i]->update();
  }

  for (int i = 0; i < MODULE_COUNT; ++i)
  {
    modules[i]->update(pkg);
  }

  if (btnLeft.isDownNow()) { openGUIScreen(currentlyDisplayedModule - 1); }
  else if (btnRight.isDownNow()) { openGUIScreen(currentlyDisplayedModule + 1); }

  if (btnUp.isDownNow()) { pkg.vcursor--; }
  if (btnDown.isDownNow()) { pkg.vcursor++; }
  if (pkg.vcursor < 0) { pkg.vcursor = 0; }
  if (pkg.vcursor >= modules[currentlyDisplayedModule]->getControlRows())
  {
    pkg.vcursor = modules[currentlyDisplayedModule]->getControlRows() - 1;
  }

  modules[currentlyDisplayedModule]->drawGUI(display);
  drawGUIvCursor();
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
  display.print(" - ");
  display.print(modules[currentlyDisplayedModule]->getName());
}

void drawGUIvCursor()
{
  for (int i = 0; i < 4; ++i)
  {
    display.setCursor(19, i);
    if (pkg.vcursor == i) { display.print("*"); }
    else { display.print(" "); }
  }
}
