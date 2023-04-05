#include "RFID.hpp"
#include "secretData.hpp"

#include <SPI.h>
#include <WiFi.h>

// WIFI_SSID and WIFI_PASS are data taken from the file "secretData.hpp"
const char ssid[] = WIFI_SSID;
const char pass[] = WIFI_PASS;
const uint8_t ss_pin = 21;
const uint8_t rst_pin = 22;

int status = WL_IDLE_STATUS;
int blockNum = 2;
byte blockData [16] = {"92900548"};

RFID rfid(ss_pin, rst_pin);

void setup() {
  // Serial initialization
  Serial.begin(9600);
  while (!Serial) { }

  // RFID initialization
  rfid.begin();

  // WiFi initialization
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: "); Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  Serial.println("You're connected to the network");
}

void loop() {
//  Results writeResult = rfid.write(blockNum, blockData);
  Results readResult = rfid.read(blockNum);
//  if (writeResult != Results::Nothing)
//  {
//    Serial.print("Writing result: "); Serial.println(writeResult);
//  }
  if (readResult != Results::Nothing)
  {
    Serial.print("Reading result: "); Serial.println(readResult);
    if (readResult == Results::Successful)
    {
      Serial.print("Data: "); Serial.println(rfid.getData());
    }
  }
}
