#include "Module.h"
#ifndef OUTPUTS_MODULE_HPP
#define OUTPUTS_MODULE_HPP

class OutputsModule : public Module
{
public:
    OutputsModule(int ledPin, int fanPin, int fanEN);

    virtual const char* getName() const;
    virtual int getControlRows() const;

    virtual void drawGUI(LiquidCrystal_I2C& display);
    virtual void update(ControlPackage& pkg);
    virtual void begin();

private:
    ControlPackage _pkg;

    int _ledPin;
    float _ledStrength;

    int _fanPin;
    int _fanEN;
    float _fanStrength;

    void initFanPWM();
    void writeFanPWM(int pin, int value);
    void drawRow(LiquidCrystal_I2C& display, float& strength, const char* name, int rowIndex);
};

#endif

