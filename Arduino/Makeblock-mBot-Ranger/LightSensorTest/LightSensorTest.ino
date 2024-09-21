/*! Test für die Lichtsensoren */
#include <MeAuriga.h>

MeLightSensor lightSensorRight(PORT_11); // Der Sensor neben Port 2
MeLightSensor lightSensorLeft(PORT_12);  // Der Sensor neben Port 9

void setup() {
  Serial.begin(115200);
}


void loop() {
  // Lichtsensoren auslesen
  int right = lightSensorRight.read();
  int left = lightSensorLeft.read();

  // Werte via serieller Verbindung an PC senden
  Serial.print("min:0,max:1000,");
  Serial.print("left:");
  Serial.print(left);
  Serial.print(",right:");
  Serial.println(right);
  // alle 50 ms
  delay(100);
}

