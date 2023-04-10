#include "RFID.hpp"

// RFID sensor initialization
RFID::RFID(uint8_t ss_pin, uint8_t rst_pin) : _rfid(ss_pin, rst_pin)
{
  for (byte i = 0; i < 6; i++)
  {
    _key.keyByte[i] = 0xFF;
  }
}

void RFID::begin()
{
  SPI.begin();
  _rfid.PCD_Init();
}

bool RFID::hasCard()
{
  if (!_rfid.PICC_IsNewCardPresent() || !_rfid.PICC_ReadCardSerial())
  {
    return false;
  }
  return true;
}

String RFID::getData()
{
    return _data;
}

Results RFID::write(int blockNum, byte blockData[])
{
  _status = _rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &_key, &(_rfid.uid));
  if (_status != MFRC522::STATUS_OK)
    return Results::AuthenticationError;

  _status = _rfid.MIFARE_Write(blockNum, blockData, 16);
  if (_status != MFRC522::STATUS_OK)
  {
    Serial.println(MFRC522::GetStatusCodeName(_status));
    return Results::WritingError;
  }

  return Results::Successful;
}

Results RFID::read(int blockNum)
{
  _status = _rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &_key, &(_rfid.uid));
  if (_status != MFRC522::STATUS_OK)
     return Results::AuthenticationError;
  
  byte bufferSize = 18;
  byte readBlockData[bufferSize];
  _status = _rfid.MIFARE_Read(blockNum, readBlockData, &bufferSize);
  if (_status != MFRC522::STATUS_OK)
  {
    Serial.println(MFRC522::GetStatusCodeName(_status));
    return Results::ReadingError;
  }

  _data = "";
  for (int i = 0 ; i < 16 ; i++)
    _data += readBlockData[i];
  
  return Results::Successful;
}
