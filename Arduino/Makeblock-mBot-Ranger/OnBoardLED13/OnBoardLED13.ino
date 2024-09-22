// Eingebaute LED auf dem Arduino-Board blinken lassen

int BlueLed = LED_BUILTIN; // Pin 13

void setup() {
  pinMode( BlueLed, OUTPUT);
}

void loop() {
  digitalWrite( BlueLed, HIGH);
  delay (1000);
  digitalWrite( BlueLed, LOW);
  delay (1000);
}
