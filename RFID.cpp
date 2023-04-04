#include "RFID.hpp"

// RFID sensor initialization
RFID::RFID(uint8_t ss_pin, uint8_t rst_pin) : _rfid(ss_pin, rst_pin) { }

void RFID::begin()
{
  SPI.begin();
  _rfid.PCD_Init();  
}

String RFID::read()
{
  // Checks if there is a card in the sensor and if so, if it is a new card
  if (!_rfid.PICC_IsNewCardPresent() || !_rfid.PICC_ReadCardSerial())
  {
    return "";
  }

  // Converts data from binary to hexadecimal separated by colons
  String idData = "";
  for (byte i = 0; i < _rfid.uid.size; i++)
  {
    idData += (_rfid.uid.uidByte[i] < 0x10 ? "0" : "") + String(_rfid.uid.uidByte[i], HEX) + (i!=3 ? ":" : "");
  }
  idData.toUpperCase();
  
  _rfid.PICC_HaltA();
  _rfid.PCD_StopCrypto1();

  return idData;
}