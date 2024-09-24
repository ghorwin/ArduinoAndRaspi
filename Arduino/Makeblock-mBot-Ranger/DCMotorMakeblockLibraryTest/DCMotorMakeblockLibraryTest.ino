/* Testprogramm für die Ansteuerung der DC Motoren via Makeblock Bibliothek */
#include <MeAuriga.h>

MeEncoderOnBoard Encoder_1(SLOT1);
MeEncoderOnBoard Encoder_2(SLOT2);

// Für präzise Messung der Geschwindigkeit (und damit Position) der Motoren, 
// werden die Pulse via Interruptfunktionen hoch/runtergezählt.
// Jedes Mal, wenn der Interrupt-Pin eines Encoders von LOW auf HIGH wechselt (RISING),
// wird die jeweilige isr_process_encoderX() Funktion aufgerufen und zählt einen 
// Pulse hoch.

// Interruptfunktion für Encoder 1
void isr_process_encoder1(void) {
  if (digitalRead(Encoder_1.getPortB()) == 0)
    Encoder_1.pulsePosMinus();
  else
    Encoder_1.pulsePosPlus();
}

// Interruptfunktion für Encoder 2
void isr_process_encoder2(void) {
  if (digitalRead(Encoder_2.getPortB()) == 0)
    Encoder_2.pulsePosMinus();
  else
    Encoder_2.pulsePosPlus();
}


int lastOutputMillis;

void setup() {
  // Festlegen der Interruptfunktionen für das Messen/Zählen der Bewegung
  attachInterrupt(Encoder_1.getIntNum(), isr_process_encoder1, RISING);
  attachInterrupt(Encoder_2.getIntNum(), isr_process_encoder2, RISING);
  Serial.begin(115200);
  
  // Interne Timer der PWM auf 8KHz programmieren
  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);

  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);

  // Variable für gelegentliche Ausgaben auf die serielle Schnittstelle
  lastOutputMillis = millis();
}

void loop() {
  // von der seriellen Schnittstelle lesen
  if (Serial.available()) {
    // Zeichen 0...6 werden gelesen
    char a = Serial.read();
    switch(a) {
      case '0':
        Encoder_1.setTarPWM(0);
        Encoder_2.setTarPWM(0);
      break;
      case '1':
        Encoder_1.setTarPWM(100);
        Encoder_2.setTarPWM(-100);
      break;
      case '2':
        Encoder_1.setTarPWM(200);
        Encoder_2.setTarPWM(-200);
      break;
      case '3':
        Encoder_1.setTarPWM(255);
        Encoder_2.setTarPWM(-255);
      break;
      case '4':
        Encoder_1.setTarPWM(-100);
        Encoder_2.setTarPWM(100);
      break;
      case '5':
        Encoder_1.setTarPWM(-200);
        Encoder_2.setTarPWM(200);
      break;
      case '6':
        Encoder_1.setTarPWM(-255);
        Encoder_2.setTarPWM(255);
      break;
      default:
      break;
    }
  }

  // In der loop() Funktion wird die Geschwindigkeit im Motor geregelt
  Encoder_1.loop();
  Encoder_2.loop();

  // alle 100 Millisekunden die Geschwindigkeit ausgeben
  if (millis() > lastOutputMillis + 100) {
    lastOutputMillis = millis();
    // Geschwindigkeit in Umdrehungen pro Minute (rpm) auslesen und ausgeben
    Serial.print("Speed 1:");
    Serial.print(Encoder_1.getCurrentSpeed());
    Serial.print(",Speed 2:");
    Serial.println(Encoder_2.getCurrentSpeed());
  }
}

