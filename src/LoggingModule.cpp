#include "LoggingModule.h"

LoggingModule::LoggingModule(SensorsModule& sensors, OutputsModule& outputs) : _sensors(sensors), _outputs(outputs)
{

}

const char* LoggingModule::getName() const
{
    return "Logging";
}

int LoggingModule::getControlRows() const
{
    return 1;
}

void LoggingModule::drawGUI(LiquidCrystal_I2C& display)
{
  display.setCursor(0, 0);
  display.print("Log Now");
}

void LoggingModule::update(ControlPackage& pkg)
{
    _pkg = pkg;
}

void LoggingModule::begin()
{
    if (_pkg.btnSubmit->isDownNow())
    {
        logData();
    }
}

void LoggingModule::logData()
{

}