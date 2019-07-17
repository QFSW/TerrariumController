#include "OutputsModule.h"

OutputsModule::OutputsModule(int ledPin, int fanPin, int fanEN) : _ledPin(ledPin), _fanPin(fanPin), _fanEN(fanEN)
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

void OutputsModule::initFanPWM()
{
    TCCR1A = 0;           // undo the configuration done by...
    TCCR1B = 0;           // ...the Arduino core library
    TCNT1  = 0;           // reset timer
    TCCR1A = _BV(COM1A1)  // non-inverted PWM on ch. A
           | _BV(COM1B1)  // same on ch; B
           | _BV(WGM11);  // mode 10: ph. correct PWM, TOP = ICR1
    TCCR1B = _BV(WGM13)   // ditto
           | _BV(CS10);   // prescaler = 1
    ICR1   = 320;         // TOP = 320

    // Set the PWM pins as output.
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
}

void OutputsModule::writeFanPWM(int pin, int value)
{
    switch (pin)
    {
        case 9:
            OCR1A = value;
            break;
        case 10:
            OCR1B = value;
            break;
        default:
            // no other pin will work
            break;
    }
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

    if (_pkg.vcursor == rowIndex)
    {
        const float changeSpeed = 100.0 / 1000 / 2;
        float strengtDelta = changeSpeed * _pkg.deltaTime;
        if (_pkg.btnSubmit->isDown()) { strength += strengtDelta; }
        if (_pkg.btnCancel->isDown()) { strength -= strengtDelta; }

        if (strength > 100) { strength = 100; }
        if (strength < 0) { strength = 0; }
    }
}

void OutputsModule::update(ControlPackage& pkg)
{
    _pkg = pkg;
    analogWrite(_ledPin, (int)2.55 * _ledStrength);
    writeFanPWM(_fanPin, (int)3.20 * _fanStrength);
    digitalWrite(_fanEN, _fanStrength > 0 ? HIGH : LOW);
}

void OutputsModule::begin()
{
    pinMode(_ledPin, OUTPUT);
    pinMode(_fanEN, OUTPUT);
    initFanPWM();
}