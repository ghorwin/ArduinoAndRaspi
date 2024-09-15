void setup() {
  // Serielle Verbindung aktivieren und Baudrate setzen
  Serial.begin(115200);
}

void loop() {
  double tempSensor1 = random(10,40);
  double tempSensor2 = random(5,15);

  // Werte im Format: "<Beschreibung>:<Wert>, <Beschreibung>:<Wert>, ..." ausgeben
  Serial.print("min:");
  Serial.print(0); // To freeze the lower limit
  Serial.print(",max:");
  Serial.print(50); // To freeze the upper limit
  Serial.print(",");
  Serial.print("Sensor 1:");
  Serial.print(tempSensor1);
  Serial.print(",");
  Serial.print("Sensor 2:");
  Serial.println(tempSensor2);
  delay(2000);
}
