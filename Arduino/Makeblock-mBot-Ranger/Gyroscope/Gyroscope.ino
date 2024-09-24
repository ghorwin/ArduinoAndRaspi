/*! Testprogramm für den Neigungssensor */
#include <MeAuriga.h>


MeGyro gyro(0, GYRO_DEFAULT_ADDRESS);


void setup() {
  Serial.begin(115200);

  // Klasse initialisieren
  gyro.begin();

}

void loop() {
  // Aktualisiere Zustand des gyro-Objects (lesen Sensoren aus und berechne Winkel/Beschleunigungen)
  // Alternativ kann man auch fast_update() verwenden
  gyro.update();

  // greife auf die Sensordaten zu
  Serial.print("Angle-X:");
  Serial.print(gyro.getAngleX());
  Serial.print(",Angle-Y:");
  Serial.print(gyro.getAngleY());
  Serial.print(",Angle-Z:");
  Serial.print(gyro.getAngleZ());

  Serial.print(",Gyro-X:");
  Serial.print(gyro.getGyroX());
  Serial.print(",Gyro-Y:");
  Serial.print(gyro.getGyroY());
  Serial.print(",Gyro-Z:");
  Serial.println(gyro.getGyroZ());

  delay(100);
}
