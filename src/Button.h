#include <Arduino.h>
#ifndef BUTTON_HPP
#define BUTTON_HPP

class Button
{
public:
  Button(int pin);
  
private:
  bool _down = false;
  bool _wasDown = false;

  int _pin;
};

#endif

