/*! Test für den Temperatursensor */
#include <MeAuriga.h>

// Der OnBoard-Temperatursensor wird über Port 13 angesprochen
MeOnBoardTemp tempSensor(PORT_13);

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("Analogwert:");
  Serial.print(tempSensor.readAnalog());
  Serial.print(",Temperaturwert:");
  Serial.println(tempSensor.readValue());
  delay(15000);
}
