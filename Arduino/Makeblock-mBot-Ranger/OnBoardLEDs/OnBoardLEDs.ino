/*! Programm für den Arduino Mega */

// Auf dem Auriga Board sind die LEDs an Pin 0 und 1 geklemmt und mit +5V verbunden
int BlueLed = 0;
int RedLed  = 1;

void setup() {
  pinMode( BlueLed, OUTPUT);
  pinMode( RedLed, OUTPUT);
}

void loop() {
  digitalWrite( BlueLed, LOW);  // Blau anschalten
  digitalWrite( RedLed, HIGH);  // Rot ausschalten
  delay (1000);
  digitalWrite( BlueLed, HIGH); // Blau ausschalten
  digitalWrite( RedLed, LOW);   // Rot anschalten
  delay (1000);
}
