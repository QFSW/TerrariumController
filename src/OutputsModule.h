#include "Module.h"
#ifndef OUTPUTS_MODULE_HPP
#define OUTPUTS_MODULE_HPP

class OutputsModule : public Module
{
public:
    OutputsModule(int ledPin);

    virtual const char* getName() const;
    virtual int getControlRows() const;

    virtual void drawGUI(LiquidCrystal_I2C& display);
    virtual void update();
    virtual void begin();

private:
    int _ledPin;
    float _ledStrength;
};

#endif

