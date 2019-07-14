#include "Module.h"
#ifndef OUTPUTS_MODULE_HPP
#define OUTPUTS_MODULE_HPP

class OutputsModule : public Module
{
public:
    OutputsModule(int ledPin, int fanPin);

    virtual const char* getName() const;
    virtual int getControlRows() const;

    virtual void drawGUI(LiquidCrystal_I2C& display);
    virtual void update();
    virtual void begin();

private:
    int _ledPin;
    float _ledStrength;

    int _fanPin;
    float _fanStrength;

    void drawRow(LiquidCrystal_I2C& display, float& strength, const char* name, int rowIndex);
};

#endif

