#include "SensorsModule.h"
#include "OutputsModule.h"
#ifndef LOGGING_MODULE_HPP
#define LOGGING_MODULE_HPP

class LoggingModule : public Module
{
public:
    LoggingModule(SensorsModule& sensors, OutputsModule& outputs);

    virtual const char* getName() const;
    virtual int getControlRows() const;

    virtual void drawGUI(LiquidCrystal_I2C& display);
    virtual void update(ControlPackage& pkg);
    virtual void begin();

private:
    int _lastLogTime = 0;
    SensorsModule& _sensors;
    OutputsModule& _outputs;
    ControlPackage _pkg;

    void logData();
};

#endif

