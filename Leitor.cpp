#include "Leitor.hpp"

MFRC522 rfid(SS_PIN, RST_PIN);

void Leitor_Config()
{
  SPI.begin();
  rfid.PCD_Init();  
}

String Leitor_Read()
{
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
  {
    return "";
  }

  String idData = "";
  for (byte i = 0; i < rfid.uid.size; i++)
  {
    idData += (rfid.uid.uidByte[i] < 0x10 ? "0" : "") + String(rfid.uid.uidByte[i], HEX) + (i!=3 ? ":" : "");
  }
  idData.toUpperCase();
  
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  return idData;
}
