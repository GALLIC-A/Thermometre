#pragma once
//preotection contre les inclusions répétées

#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port G4
#define ONE_WIRE_BUS 4
#define TEMPERATURE_PRECISION 9
// set the resolution to 10 bit (Can be 9 to 12 bits .. lower is faster)
// ça change les incréments : par exemple 10=0.25°C, 9=0.5°C, etc

class SensorReader {
public:
    SensorReader();
    void begin();
    float readTemperature();

private:
    OneWire oneWire;
    DallasTemperature sensors;
    DeviceAddress adresseSonde;
};