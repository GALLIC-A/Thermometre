// // #include <Arduino.h>

// // void setup() {
// //   Serial.begin(115200);
// //   delay(1000);
// //   Serial.println("Bonjour");
// // }

// // void loop() {
// //   Serial.println("a");
// //   delay(2000);
// // }


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


////////////////// UNE FOIS QU'ON CONNAIT LES ADRESSES DE LA SONDE ON PEUT LIRE, C'EST CE QUE FAIT LE CODE CI DESSOUS


/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
  Based on the Dallas Temperature Library example
*********/

#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port G4
#define ONE_WIRE_BUS 4
#define TEMPERATURE_PRECISION 10
 
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
 
// Tableaux contenant l'adresse de chaque sonde OneWire | arrays to hold device addresses
DeviceAddress insideThermometer = { 0x28,  0xBA,  0xFE,  0x87,  0x0,  0x0,  0x0,  0x8D };

 
void setup() {
  Serial.begin(115200);
  
  // Start up the library
  sensors.begin();
 
  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");
 
  // report parasite power requirements
  Serial.print("Parasite power is: "); 
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");
 
  // Vérifie sir les capteurs sont connectés | check and report if sensors are conneted 
  if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0"); 
 
  // set the resolution to 9 bit per device
  sensors.setResolution(insideThermometer, TEMPERATURE_PRECISION);
 
  // On vérifie que le capteur st correctement configuré | Check that ensor is correctly configured
  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(insideThermometer), DEC); 
  Serial.println();
}
 
void printTemperature(String label, DeviceAddress deviceAddress){
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print(label);
  if (tempC == -127.00) {
    Serial.print("Error getting temperature");
  } else {
    Serial.print(" Temp C: ");
    Serial.print(tempC);
    Serial.print(" Temp F: ");
    Serial.println(DallasTemperature::toFahrenheit(tempC));
  }  
}
 
void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.println("DONE");
 
  // print the device information
  printTemperature("Inside : ", insideThermometer);
  
  delay(5000);
}