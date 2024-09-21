/* Testprogramm für den Sound-Sensor am Auriga-Board.
 * 
 * ACHTUNG: beim Auriga ist der Sound-Sensor am Port 14 angeschlossen.
 */
#include <MeAuriga.h>

MeSoundSensor mySound(PORT_14);

void setup() {
  Serial.begin(115200);
}

void loop()
{
  Serial.print("value:");
  Serial.println(mySound.strength() );
  delay(50);
}

