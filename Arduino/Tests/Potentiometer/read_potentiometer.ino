// speichern des am Anschluss A0 gelesenen Werts
int ReglerWert;

// Potentiometer am Anschluss A0
int REGLER_PIN = A0;

void setup()
{
  Serial.begin(115200);
}

void loop() { 
  // Wert des Potentiometers lesen: 0...1023
  ReglerWert = analogRead(REGLER_PIN); 

  Serial.print("Poti:");
  Serial.println(ReglerWert);

  delay(1000);
}

