/* Testprogramm für die Ansteuerung der DC-Motoren mittels Arduino Pin Bibliothek */
#include "MeAuriga.h"

#define PWMA  11 // Motor A/Links
#define DIRA1 49
#define DIRA2 48
#define PWMB  10 // Motor B/Rights
#define DIRB1 47
#define DIRB2 46

void setup() {
  // PWM und Richtungspins setzen
  pinMode(PWMA,  OUTPUT);  
  pinMode(DIRA1, OUTPUT); 
  pinMode(DIRA2, OUTPUT);
  pinMode(PWMB,  OUTPUT);  
  pinMode(DIRB1, OUTPUT); 
  pinMode(DIRB1, OUTPUT);

  Serial.begin(115200);
  delay (1000);
}

int speed = 0;
bool upward = true;

void loop() {
  if (upward)
    speed += 5;
  else
    speed -= 5;
  if (speed > 255) {
    upward = false;
    speed = 255;
  }
  if (speed < -255) {
    upward = true;
    speed = -255;
  }
  Serial.println(speed);

  if (speed >= 0) {
    analogWrite (PWMA,  speed);
    digitalWrite(DIRA1, LOW);
    digitalWrite(DIRA2, HIGH);
    analogWrite (PWMB,  speed);
    digitalWrite(DIRB1, HIGH);
    digitalWrite(DIRB2, LOW);
  }
  else {
    analogWrite (PWMA,  -speed);
    digitalWrite(DIRA1, HIGH);
    digitalWrite(DIRA2, LOW);
    analogWrite (PWMB,  -speed);
    digitalWrite(DIRB1, LOW);
    digitalWrite(DIRB2, HIGH);
  }
  delay(50);
}
