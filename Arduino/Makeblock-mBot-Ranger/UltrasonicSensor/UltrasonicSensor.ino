#include "MeAuriga.h"

// Der Utrasonic-Sensor ist an Steckplatz 6 eingesteckt
MeUltrasonicSensor ultraSensor(PORT_6);

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("Distance : ");
  Serial.print(ultraSensor.distanceCm() );
  Serial.println(" cm");
  delay(100); // Das minimale Messinterval ist 100 ms
}
