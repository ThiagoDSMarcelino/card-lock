#include "RFID.hpp"
#include "Data.hpp"

const uint8_t ss_pin = 21;
const uint8_t rst_pin = 22;

int blockNum = 2;
byte blockData [16] = { "92900548" };

RFID rfid(ss_pin, rst_pin);

void setup() {
  // Serial initialization
  Serial.begin(9600);
  while (!Serial) { }

  // RFID initialization
  rfid.begin();
}

void loop() {
  if (!rfid.hasCard())
  {
    return;
  }
  
  Serial.println("Tem cartão");

//  Results writeResult = rfid.write(blockNum, blockData);
//  Serial.print("Writing result: "); Serial.println(writeResult);
  Results readResult = rfid.read(blockNum);
  if (readResult != Results::Nothing)
  {
    Serial.print("Reading result: "); Serial.println(readResult);
    if (readResult == Results::Successful)
    {
      Serial.print("Data: "); Serial.println(rfid.getData());
    }
  }
}
