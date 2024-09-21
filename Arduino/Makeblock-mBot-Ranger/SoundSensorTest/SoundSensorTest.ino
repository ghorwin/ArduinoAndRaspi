/* Testprogramm für den Sound-Sensor am Auriga-Board.
 * 
 * ACHTUNG: beim Auriga ist der Sound-Sensor am Port 14 angeschlossen.
 */
#include <MeAuriga.h>

MeSoundSensor soundSensor(PORT_14);

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("value:");
  Serial.println(soundSensor.strength() );
  delay(50);
}

