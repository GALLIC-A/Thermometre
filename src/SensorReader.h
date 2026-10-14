#pragma once
//preotection contre les inclusions répétées

#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port G4
#define ONE_WIRE_BUS 4
#define TEMPERATURE_PRECISION 10

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