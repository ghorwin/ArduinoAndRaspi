/*! Test für den Buzzer */
#include <MeAuriga.h>

#define buzzerOn()  pinMode(45,OUTPUT),analogWrite(45, 127)
#define buzzerOff() pinMode(45,OUTPUT),analogWrite(45, 0)

void setup() {
  Serial.begin(115200);
}

void loop() {
  buzzerOn();
  delay(1000);
  buzzerOff();
  delay(1000);
}

