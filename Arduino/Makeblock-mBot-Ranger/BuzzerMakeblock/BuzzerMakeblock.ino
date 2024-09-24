/*! Testprogramm für den Buzzer mithilfe der Klasse MeBuzzer */
#include <MeAuriga.h>

#define BUZZER_PIN 45

MeBuzzer buzzer;

void setup()  {
  buzzer.setpin(BUZZER_PIN);
  buzzer.noTone();
}

void loop()  {
  buzzer.tone(262, 250);   //NOTE_C4
  buzzer.tone(294, 250);   //NOTE_D4
  buzzer.tone(330, 250);   //NOTE_E4
  delay(2000);

  buzzer.tone(587, 250);   //NOTE_D5
  buzzer.tone(659, 250);   //NOTE_E5
  buzzer.tone(523, 250);   //NOTE_C5
  delay(2000);
}
