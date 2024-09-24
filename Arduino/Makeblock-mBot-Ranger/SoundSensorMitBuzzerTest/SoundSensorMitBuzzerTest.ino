/* Testprogramm für den Sound-Sensor am Auriga-Board.
 * 
 * ACHTUNG: beim Auriga ist der Sound-Sensor am Port 14 angeschlossen.
 */
#include <MeAuriga.h>

MeSoundSensor soundSensor(PORT_14);

#define buzzerOn()  pinMode(45,OUTPUT),analogWrite(45, 127)
#define buzzerOff() pinMode(45,OUTPUT),analogWrite(45, 0)

unsigned long buzzerOnMillis;
unsigned long buzzerOffMillis;

void setup() {
  Serial.begin(115200);
  buzzerOnMillis = millis();
  buzzerOffMillis = buzzerOnMillis + 500;
}


void loop() {
  if (millis() > buzzerOnMillis) {
    buzzerOn();
    buzzerOnMillis = millis() + 2000;
  }
  if (millis() > buzzerOffMillis) {
    buzzerOff();
    buzzerOffMillis = buzzerOnMillis + 500;
  }
  Serial.print("value:");
  Serial.println(soundSensor.strength() );
  delay(50);
}

