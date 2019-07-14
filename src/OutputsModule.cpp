#include "OutputsModule.h"

OutputsModule::OutputsModule(int ledPin) : _ledPin(ledPin)
{

}

const char* OutputsModule::getName() const
{
    return "Outputs";
}

int OutputsModule::getControlRows() const
{
    return 1;
}

void OutputsModule::drawGUI(LiquidCrystal_I2C& display)
{
    display.setCursor(0, 0);
    display.print("LED: ");
    display.print((int)_ledStrength);
    display.print("%   ");

    const float changeSpeed = 100.0 / 1000 / 2;
    //float strengtDelta = changeSpeed * deltaTime;
    //if (btnSubmit.isDown()) { _ledStrength += strengtDelta; }
    //if (btnCancel.isDown()) { _ledStrength -= strengtDelta; }

    if (_ledStrength > 100) { _ledStrength = 100; }
    if (_ledStrength < 0) { _ledStrength = 0; }
}

void OutputsModule::update()
{
    analogWrite(_ledPin, (int)2.55 * _ledStrength);
}

void OutputsModule::begin()
{
    pinMode(_ledPin, OUTPUT);
}