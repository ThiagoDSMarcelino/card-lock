#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

enum Results
{
  Successful,
  AuthenticationError,
  ReadingError,
  WritingError
};

class RFID
{
  public:
    RFID(uint8_t ss_pin, uint8_t rst_pin);
    void begin();
    bool hasCard();
    String getData();
    Results write(byte blockData[]);
    Results read();
  
  private:
    int _blockNum = 2;
    String _data = "";
    MFRC522 _rfid;
    MFRC522::MIFARE_Key _key;
    MFRC522::StatusCode _status;
};
