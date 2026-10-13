#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Bonjour");
}

void loop() {
  Serial.println("a");
  delay(2000);
}