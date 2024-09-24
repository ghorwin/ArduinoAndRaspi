/* Testprogramm für die Ansteuerung der DC-Motoren mittels Arduino Pin Bibliothek */
#include "MeAuriga.h"

#define PWMA  11 //Motor Left
#define DIRA1 49
#define DIRA2 48
#define PWMB  10 //Motor Right
#define DIRB1 47
#define DIRB2 46

int full_speed = 120; // full
int half_speed =  60; // half
int slow_speed =  30; // turn
int stop       =   0; // stop

unsigned long stage_millis;
int stage = 0;

void setup() {
  // PWM und Richtungspins setzen
  pinMode(PWMA,  OUTPUT);  
  pinMode(DIRA1, OUTPUT); 
  pinMode(DIRA2, OUTPUT);
  pinMode(PWMB,  OUTPUT);  
  pinMode(DIRB1, OUTPUT); 
  pinMode(DIRB1, OUTPUT);

  stage_millis = millis();

  delay (1000);
}


void loop() {
  int newStage = stage;
  if (millis() > stage_millis) {
    ++newStage;
    newStage = newStage % 4; // we have only 8 stages
  }

  if (newStage != stage) {
    stage = newStage;

    switch (stage) {
      // straight on - half
      case 0 :
        analogWrite (PWMA,  half_speed);
        digitalWrite(DIRA1, LOW);
        digitalWrite(DIRA2, HIGH);
        analogWrite (PWMB,  half_speed);
        digitalWrite(DIRB1, HIGH);
        digitalWrite(DIRB2, LOW);
        stage_millis += 2000;
      break;

      // turn left slow
      case 1 : 
        analogWrite (PWMA,  slow_speed);
        digitalWrite(DIRA1, LOW);
        digitalWrite(DIRA2, HIGH);
        analogWrite (PWMB,  slow_speed);    
        digitalWrite(DIRB1, LOW);
        digitalWrite(DIRB2, HIGH);
        stage_millis += 1000;
      break;

      // straight on - fast
      case 2 :
        analogWrite (PWMA,  full_speed);
        digitalWrite(DIRA1, LOW);
        digitalWrite(DIRA2, HIGH);
        analogWrite (PWMB,  full_speed);
        digitalWrite(DIRB1, HIGH);
        digitalWrite(DIRB2, LOW);
        stage_millis += 2000;
      break;

      // turn left - fast
      case 3 : 
        analogWrite (PWMA,  half_speed);
        digitalWrite(DIRA1, LOW);
        digitalWrite(DIRA2, HIGH);
        analogWrite (PWMB,  half_speed);    
        digitalWrite(DIRB1, LOW);
        digitalWrite(DIRB2, HIGH);
        stage_millis += 500;
      break;
    } // switch
  }
  delay(100);  
}

