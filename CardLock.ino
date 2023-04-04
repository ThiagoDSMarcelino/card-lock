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

RFID rfid(ss_pin, rst_pin);

void setup() {
  // Serial initialization
  Serial.begin(9600);
  while (!Serial) { }

  // RFID initialization
  rfid.begin();

  // WiFi initialization
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    
    status = WiFi.begin(ssid, pass);
    
    delay(10000);
  }
  Serial.print("You're connected to the network");
}

void loop() {
  String idData = rfid.read();
  if (idData != "")
  {
    Serial.println(idData);  
  }
}