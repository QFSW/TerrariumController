#ifndef MODULE_HPP
#define MODULE_HPP

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "ControlPackage.h"

class Module
{
public:
  virtual const char* getName() const = 0;
  virtual int getControlRows() const = 0;

  virtual void drawGUI(LiquidCrystal_I2C& display) = 0;
  virtual void update(ControlPackage& pkg) = 0;
  virtual void begin() = 0;
};

#endif

