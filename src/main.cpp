// CODE CHOPPÉ SUR https://www.doritique.fr/Articles/View_Article.php?num_article=95

/////// POUR CONNAÎTRE LES ADRESSES DE LA SONDE :

// #include <OneWire.h>

// OneWire ds(4); // g4

// byte i;
// byte type_s;
// byte data[12];
// byte addr[8];

// void OneWireScanner(){
//     if(!ds.search(addr)){
//     Serial.println("No more addresses.");
//     Serial.println();
//     ds.reset_search();
//     return;
//   }
//   Serial.println("ROM = ");
//   for(i=0;i<8;i++){
//     Serial.write(' ');
//     Serial.print("0x");
//     Serial.print(addr[i], HEX);
//     if(i!=7){
//       Serial.print(", ");
//     }
//   }
//   if(OneWire::crc8(addr,7)!=addr[7]){
//     Serial.println("CRC is not valid!!!");
//     return;
//   }
//   Serial.println();
//   //the first rom byte indicate which chip
//   switch(addr[0]){
//     case 0x10:
//       Serial.println(" Chip=DS18S20");
//       type_s=1;
//       break;
//     case 0x28:
//       Serial.println(" Chip=DS18B20");//normalement je suis ici
//       type_s=0;
//       break;
//     case 0x22:
//       Serial.println(" Chip=DS1822");
//       type_s=0;
//       break;
//     default:
//       Serial.println("Device is not DS18x20 family device.");
//       return;
//   }
// }

// void setup(){
//   Serial.begin(115200);
// }

// void loop(){
//   OneWireScanner();
//   delay(5000);
// }

 

#include <Arduino.h>
#include "SensorReader.h"
#include <WiFi.h>
#include "config.h"
SensorReader sensorReader;
void connecterWiFi();
void setup() {
  Serial.begin(115200);
  sensorReader.begin();
  connecterWiFi();  
}
void loop() {
  float temperature=sensorReader.readTemperature();
  if(temperature==-127){
    Serial.println("Une erreur est survenue lors de la lecture de la sonde.");
  }else{
    Serial.print(temperature);
    Serial.println(" °C");
  }
  Serial.print("@IP : ");
  Serial.println(WiFi.localIP());
  delay(5000);//lecture toutes les 5 secondes
}
void connecterWiFi(){
  Serial.println("Tentative connexion Wi-Fi");
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println(".");
  }
  Serial.println("Connexion Wi-Fi ok");
  Serial.print("ipaddr : ");
  Serial.println(WiFi.localIP());
}