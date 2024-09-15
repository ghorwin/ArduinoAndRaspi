/* Testprogramm für die Verwendung des I2C-Protokolls am Arduino.

Man verbindet das I2C-Gerät, bspw. das LCD16x02 Display via folgender Pins:
- GND mit GND
- VCC mit +5V
- SDA mit SDA (D18)
- SCL mit SCL (D19)
*/
#include <Wire.h>

void setup() {
  // I2C Bibliothek initialisieren
  Wire.begin();

  Serial.begin(115200);
  Serial.println("---I2C Scanner---");
}

void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; ++address) {
    // Kommunikationsversuch an der Adresse
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    // Kommunikationsversuch an der Folgeadresse
    Wire.beginTransmission(address + 1);

    if (error == 0 && Wire.endTransmission() != 0) { // Special flag for SAMD Series
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("!");

      ++nDevices;
    } 
    else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");

  delay(5000);  // wait 5 seconds for next scan
}
