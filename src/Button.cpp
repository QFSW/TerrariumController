#include "Button.h"

Button::Button(int pin)
{
  _pin = pin;
}

void Button::begin()
{
  pinMode(_pin, INPUT_PULLUP);
}

void Button::update()
{
  _wasDown = _down;
  _down = !digitalRead(_pin);
}

bool Button::isDown() const
{
  return _down;
}

bool Button::isDownNow() const
{
  return _down & !_wasDown;
}

