#include "Module.h"
#include "DHT.h"
#ifndef SENSORS_MODULE_HPP
#define SENSORS_MODULE_HPP

class SensorsModule : public Module
{
public:
    SensorsModule(int dhtpin);

    virtual const char* getName() const;
    virtual int getControlRows() const;

    virtual void drawGUI(LiquidCrystal_I2C& display);
    virtual void update(ControlPackage& pkg);
    virtual void begin();

private:
    DHT _dht;
    float _temp;
    float _humidity;
};

#endif

