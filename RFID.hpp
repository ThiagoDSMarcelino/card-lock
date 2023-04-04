#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>


class RFID
{
  public:
    RFID(uint8_t ss_pin, uint8_t rst_pin);
    void begin();
    String read();
    
  private:
    MFRC522 _rfid;
};
