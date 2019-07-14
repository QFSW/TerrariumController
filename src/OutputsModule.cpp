#include "OutputsModule.h"

OutputsModule::OutputsModule(int ledPin, int fanPin) : _ledPin(ledPin), _fanPin(fanPin)
{

}

const char* OutputsModule::getName() const
{
    return "Outputs";
}

int OutputsModule::getControlRows() const
{
    return 2;
}

void OutputsModule::drawGUI(LiquidCrystal_I2C& display)
{
    drawRow(display, _ledStrength, "LEDs", 0);
    drawRow(display, _fanStrength, "Fans", 1);
}

void OutputsModule::drawRow(LiquidCrystal_I2C& display, float& strength, const char* name, int rowIndex)
{
    display.setCursor(0, rowIndex);
    display.print(name);
    display.print(": ");

    display.setCursor(14, rowIndex);
    if (strength < 10) { display.print(" "); }
    if (strength < 100) { display.print(" "); }
    display.print((int)strength);
    display.print("%");

    const float changeSpeed = 100.0 / 1000 / 2;
    //float strengtDelta = changeSpeed * deltaTime;
    //if (btnSubmit.isDown()) { strength += strengtDelta; }
    //if (btnCancel.isDown()) { strength -= strengtDelta; }

    if (strength > 100) { strength = 100; }
    if (strength < 0) { strength = 0; }
}

void OutputsModule::update()
{
    analogWrite(_ledPin, (int)2.55 * _ledStrength);
    analogWrite(_fanPin, (int)2.55 * _fanStrength);
}

void OutputsModule::begin()
{
    pinMode(_ledPin, OUTPUT);
    pinMode(_fanPin, OUTPUT);
}