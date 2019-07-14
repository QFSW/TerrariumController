#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C display(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup()
{
  display.begin(20, 4);
  display.clear();
  display.setCursor(0, 0);
  display.print("Terrarium");
}

void loop()
{

}
