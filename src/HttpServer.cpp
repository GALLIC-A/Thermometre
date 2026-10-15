#include "HttpServer.h"
HttpServer::HttpServer(SensorReader& sensorReader)
    : server(80),sensorReader(sensorReader)
{}
void HttpServer::begin() {
    server.begin();
    Serial.println("Serveur HTTP ok");
}
void HttpServer::gererClient() {
    WiFiClient client = server.available();
    if(client){
        Serial.println("Nouveau client");
        String currentLine;
        String requestLine;
        // le while lit un flux de caractères (envoyé par le navigatuer), c'est pour ça qu'on regarde si c'est une fin de ligne ou si c'est un retour chariot
        while(client.connected()){
          if(client.available()){
            char c=client.read();
            if(c=='\n'){
                // donc si retour à la ligne, on peut lire son contenu
              if(requestLine.length()==0 && currentLine.length()>0){
                  requestLine=currentLine;
              }
              // ligne vide = fin d'en-tête http
              if(currentLine.length()==0){
                  bool api=requestLine.startsWith("GET /api ");
                  float temperature=sensorReader.readTemperature();
                  envoyerReponse(client,temperature,api);
                  break;
              }
              currentLine="";
            }else if(c!='\r'){
                // sinon on continue de fabriquer la ligne
                currentLine+=c;
            }
          }
        }
        client.stop();
        Serial.println("Déconnexion du client");
        Serial.println("");
    }
}
void HttpServer::envoyerReponse(WiFiClient& client,float temperature,bool api){
    client.println("HTTP/1.1 200 OK");
    client.println(api ? "Content-Type:application/json;charset=utf-8" : "Content-Type:text/html;charset=utf-8");
    client.println("Connection: close");
    client.println();
    if(api){
        if(temperature==-127){
            client.print("{\"error\":\"erreur lecture\"}");
        }else{
            client.print("{\"temperature\":");
            client.print(temperature);
            client.print(",\"unite\":\"C°\"}");
        }
        client.println();
        return;
    }
    client.println("<!DOCTYPE html><html><head><title>Super thermomètre</title><style>html{background-color:red;color:yellow;}</style></head><body><h1>");
    if(temperature==-127){
        client.println("Erreur de lecture :(");
    }else{
        client.print(temperature);
        client.println(" C°");
    }
    client.println("</h1></body></html>");
    client.println();
}