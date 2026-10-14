#include "SensorReader.h"

//constructeur avec une liste d'initialisation
//= 1. Construire OneWire, 2. Construire sensors en lui filant l'adresse mémoire de oneWire, 3. exécuter le corps
SensorReader::SensorReader() 
    : oneWire(ONE_WIRE_BUS),sensors(&oneWire),adresseSonde{0x28,0xBA,0xFE,0x87,0x0,0x0,0x0,0x8D}
{
}

void SensorReader::begin() {
    //setup bibliothèque
    sensors.begin();

    // Vérifie si les capteurs sont connectés
   if (!sensors.getAddress(adresseSonde, 0)) Serial.println("Unable to find address for Device 0"); 

   // set the resolution to 9 bit per device
   sensors.setResolution(adresseSonde, TEMPERATURE_PRECISION);
}

float SensorReader::readTemperature() {
    sensors.requestTemperatures();
    return sensors.getTempC(adresseSonde);
}