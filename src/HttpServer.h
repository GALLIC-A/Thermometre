#pragma once

#include <WiFi.h>
#include "SensorReader.h"

class HttpServer{
    public:
        HttpServer(SensorReader& sensorReader);
        void begin();
        void gererClient();
    
    private:
        WiFiServer server;
        SensorReader& sensorReader;
        void envoyerReponse(WiFiClient& client,float temperature,bool api);
};