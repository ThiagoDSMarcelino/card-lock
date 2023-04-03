#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 21
#define RST_PIN 22

void Leitor_Config();
String Leitor_Read();
