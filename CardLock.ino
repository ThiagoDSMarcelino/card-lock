#include "RFID.hpp"
#include "Data.hpp"

const uint8_t ss_pin = 21;
const uint8_t rst_pin = 22;
const uint8_t lock_pin = 13;

byte blockData[16] = { "92900521" };

RFID rfid(ss_pin, rst_pin);

void setup() {
  // Serial initialization
  Serial.begin(9600);
  while (!Serial) { }

  
  pinMode(lock_pin, OUTPUT);
  
  // RFID initialization
  rfid.begin();
}

void loop() {
  if (!rfid.hasCard())
    return;

//  Results writeResult = rfid.write(blockData);
//  Serial.print("Writing result: "); Serial.println(writeResult);

  Results readResult = rfid.read();
  if (readResult == Results::Successful)
  {
    String resultData = rfid.getData();
    Serial.print("Data: "); Serial.println(resultData);
    for (int i = 0; i < (sizeof(collaboratorData) / sizeof(collaboratorData[0])); i++)
    {
      if (collaboratorData[i].EDV.compareTo(resultData) == 0)
      {
        digitalWrite(lock_pin, HIGH);
        Serial.println("True");
        delay(5000);
        digitalWrite(lock_pin, LOW);
        Serial.print("False");
        break;
      }
    }
  }

  delay(3000);
  ESP.restart();
}
