#include "RFID.hpp"

RFID::RFID(uint8_t ss_pin, uint8_t rst_pin)
{
  MFRC522 rfid(ss_pin, rst_pin);
  _rfid = rfid;
}

void RFID::begin()
{
  SPI.begin();
  _rfid.PCD_Init();  
}

String RFID::read()
{
  if (!_rfid.PICC_IsNewCardPresent() || !_rfid.PICC_ReadCardSerial())
  {
    return "";
  }

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
