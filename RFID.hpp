#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

enum Results
{
  Successful,
  AuthenticationError,
  ReadingError,
  WritingError,
  Nothing
};

class RFID
{
  public:
    RFID(uint8_t ss_pin, uint8_t rst_pin);
    void begin();
    String getData();
    Results write(int blockNum, byte blockData[]);
    Results read(int blockNum);
  
  private:
    String _data = "";
    MFRC522 _rfid;
    MFRC522::MIFARE_Key _key;
    MFRC522::StatusCode _status;
};
