#include "RFID.hpp"

#define SS_PIN 21
#define RST_PIN 22

RFID rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  rfid.begin();
}

void loop() {
  String idData = rfid.read();
  if (idData != "")
  {
    Serial.println(idData);  
  }
}
