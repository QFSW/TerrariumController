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

float temp;
float humidity;
float ledStrength = 0;

int time = 0;
int lastTime = 0;
int deltaTime = 0;

#define LED_PIN 3

void openGUIScreen(int index);
void drawGUIFooter();
void drawSensorGUI();
void drawOutputGUI();


#define GUI_SCREEN_COUNT 2
int currentGUI = 0;
void(*GUIScreens[GUI_SCREEN_COUNT])() =
{
  drawSensorGUI,
  drawOutputGUI
};

void setup()
{
  display.begin();
  dht.begin();
  pinMode(LED_PIN, OUTPUT);

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
  temp = dht.readTemperature();
  humidity = dht.readHumidity();

  for (int i = 0; i < BUTTON_COUNT; ++i)
  {
    btns[i]->update();
  }

  lastTime = time;
  time = millis();
  deltaTime = time - lastTime;

  if (btnLeft.isDownNow()) { openGUIScreen(currentGUI - 1); }
  else if (btnRight.isDownNow()) { openGUIScreen(currentGUI + 1); }

  analogWrite(LED_PIN, (int)2.55 * ledStrength);
  GUIScreens[currentGUI]();
}

void openGUIScreen(int index)
{
  if (index >= GUI_SCREEN_COUNT) { index = GUI_SCREEN_COUNT - 1; }
  if (index < 0) { index = 0; }
  currentGUI = index;
  display.clear();
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

void drawOutputGUI()
{
  display.setCursor(0, 0);
  display.print("LED: ");
  display.print((int)ledStrength);
  display.print("%   ");

  const float changeSpeed = 100.0 / 1000 / 2;
  float strengtDelta = changeSpeed * deltaTime;
  if (btnSubmit.isDown()) { ledStrength += strengtDelta; }
  if (btnCancel.isDown()) { ledStrength -= strengtDelta; }

  if (ledStrength > 100) { ledStrength = 100; }
  if (ledStrength < 0) { ledStrength = 0; }
}
