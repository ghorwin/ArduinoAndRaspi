/* Ranger fährt vorwärts, bis ein Hinternis erkannt wird. Nähert sich diesem an bis auf 30 cm. Macht dann eine
    180° Wende und parkt rückwärts ein. 
*/
#include <MeAuriga.h>
#include "KnightRiderLEDs.h"
#include "RGB2HSV.h"


MeEncoderOnBoard Encoder_1(SLOT1);
MeEncoderOnBoard Encoder_2(SLOT2);

// Der Utrasonic-Sensor ist an Steckplatz 6 eingesteckt
MeUltrasonicSensor ultraSensor(PORT_6);

KnightRiderLEDs leds(9);

#define APPROACH_DISTANCE 60
#define STOP_DISTANCE 20

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

enum Stages {
  /*! Bot drives forward at medium speed until obstacle is detected at 50cm or less. */
  S_ScanForward,
  /*! Bot drives forward and reduces speed as it approaches obstacle and stops at 30 cm. */
  S_ApproachEndpoint,
  /*! Bot turns around in-place 180°, until gyroscope points into opposite direction. */
  S_Turn180,
  /*! Bot parks backward */
  S_ParkBackward,
  /*! Bot goes in hybernation mode (pulses LEDs) */
  S_Hybernate 
};

int lastOutputMillis;
Stages stage = S_ScanForward;
unsigned long lastDistanceScanMillis, lastLedUpdateMillis, lastSpeedUpdateMillis;
float distanceInCm = 1000;

unsigned int pulseCounter = 0;

void setup() {
  leds.setup();

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
  lastOutputMillis = lastDistanceScanMillis = lastLedUpdateMillis = lastSpeedUpdateMillis = millis();
}


void loop() {
  // scan distance every 100 ms
  unsigned long now = millis();
  if (now > lastDistanceScanMillis + 100) {
    distanceInCm = ultraSensor.distanceCm();
    lastDistanceScanMillis = now;
  }


  // do different stuff depending on current stage
  switch (stage) {
    case S_ScanForward : {
        if (now > lastSpeedUpdateMillis + 200) {
          lastSpeedUpdateMillis = now;
          Encoder_1.setTarPWM(-200);
          Encoder_2.setTarPWM(200);
        }
        // update the LEDs 
        if (now > lastLedUpdateMillis + 100) {
          leds.step(true, 0,255,0);
          lastLedUpdateMillis = now;
        }
        // eval the distance sensor
        if (distanceInCm < APPROACH_DISTANCE) {
          stage = S_ApproachEndpoint;
        }
    } break;

    case S_ApproachEndpoint : {
        // eval the distance sensor
        if (distanceInCm < STOP_DISTANCE) {
          stage = S_Hybernate;
        }
        // compute speed as function of distance
        float relDist = distanceInCm - APPROACH_DISTANCE;
        float scale = relDist/(APPROACH_DISTANCE - STOP_DISTANCE); // 0 - when green, 1 - when red
        scale = max(0.0, scale);
        scale = min(1.0, scale);
        if (now > lastSpeedUpdateMillis + 200) {
          Serial.print("distanceInCm:");
          Serial.println(distanceInCm);
          lastSpeedUpdateMillis = now;
          Encoder_1.setTarPWM(-(20 + (1-scale)*80));
          Encoder_2.setTarPWM((20 + (1-scale)*80));
        }
        // update the LEDs 
        if (now > lastLedUpdateMillis + 100) {
          // we fade from red (distance 50) to green (distance 30)
          uint8_t hue = scale*86;
          HsvColor c(hue,255,255);
          RgbColor rgb = HsvToRgb(c);
          leds.step(true, rgb.m_r, rgb.m_g, rgb.m_b);
          lastLedUpdateMillis = now;
        }
    } break;

    case S_Hybernate : {
        Encoder_1.setTarPWM(0);
        Encoder_2.setTarPWM(0);
        // update the LEDs 
        if (now > lastLedUpdateMillis + 100) {
          pulseCounter = (pulseCounter + 10) % 512;
          uint8_t c = pulseCounter;
          if (pulseCounter > 255)
            c = 511 - pulseCounter;
          leds.m_led.setColor(0, c, 0, 0);
          leds.m_led.show();
          lastLedUpdateMillis = now;
        }
    } break;
  }

  // In der loop() Funktion wird die Geschwindigkeit im Motor geregelt
  Encoder_1.loop();
  Encoder_2.loop();
}

