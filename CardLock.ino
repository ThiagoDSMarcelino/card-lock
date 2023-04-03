#include "Leitor.hpp"

void setup() {
  Serial.begin(9600);
  Leitor_Config();
}

void loop() {
  String idData = Leitor_Read();
  if (idData != "") {
    Serial.println(idData);  
  }
}
