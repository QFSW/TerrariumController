#include "SensorsModule.h"

SensorsModule::SensorsModule(int dhtpin) : _dht(dhtpin, DHT11)
{

}

const char* SensorsModule::getName() const
{
    return "Sensors";
}

int SensorsModule::getControlRows() const
{
    return 0;
}

void SensorsModule::drawGUI(LiquidCrystal_I2C& display)
{
  display.setCursor(0, 0);
  display.print("Temperature: ");
  display.print((int)_temp);
  display.print("C   ");
  
  display.setCursor(0, 1);
  display.print("Humidity: ");
  display.print((int)_humidity);
  display.print("%   ");
}

void SensorsModule::update()
{
    _temp = _dht.readTemperature();
    _humidity = _dht.readHumidity();
}

void SensorsModule::begin()
{
    _dht.begin();
}