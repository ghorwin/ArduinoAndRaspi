/* 
  Beispielprogramm für eine LED RGB mit "Common Anode", 
  d.h. Anschluss von +5V an den längsten Fuß der RGB LED.

  HIGH an einem der RGB Pins heißt "aus".
*/
#define  LED_ROT   5
#define  LED_GREEN 6
#define  LED_BLUE  3

void setup()  {
  pinMode(LED_ROT, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  // alle LEDs aussschalten
  analogWrite(LED_ROT, 255);  
  analogWrite(LED_GREEN, 255);
  analogWrite(LED_BLUE, 255);
}

void loop()  {
  for (int i=0; i<255; i+=5) {
     analogWrite(LED_ROT, 255-i);  
     delay(20);
  }
  analogWrite(LED_ROT, 255);   // rot ausschalten
  for (int i=0; i<255; i+=5) {
     analogWrite(LED_GREEN, 255-i);
     delay(20);
  }
  analogWrite(LED_GREEN, 255);   // grün ausschalten
  for (int i=0; i<255; i+=5) {
     analogWrite(LED_BLUE, 255-i); 
     delay(20);
  }
  analogWrite(LED_BLUE, 255);   // blau einschalten
  for (int i=0; i<255; i+=5) {
     analogWrite(LED_ROT, 255-i);  
     analogWrite(LED_BLUE, 255-i);  
     delay(20);
  }
  analogWrite(LED_ROT, 255);   // rot ausschalten
  analogWrite(LED_BLUE, 255);   // blau ausschalten
  for (int i=0; i<255; i+=5) {
     analogWrite(LED_ROT, 255-i);  
     analogWrite(LED_GREEN, 255-i);  
     delay(20);
  }
  analogWrite(LED_ROT, 255);   // rot ausschalten
  analogWrite(LED_GREEN, 255);   // blau ausschalten
  delay(1000);
}