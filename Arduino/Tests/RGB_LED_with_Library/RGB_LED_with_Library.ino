/* 
  Beispielprogramm für eine LED RGB mit "Common Anode", 
  d.h. Anschluss von +5V an den längsten Fuß der RGB LED.

  Verwendet wird die Bibliothek RGB von WILMOUTH Steven

  HIGH an einem der RGB Pins heißt "aus".
*/

#include <RGBLed.h>

#define  RED_PIN   5
#define  GREEN_PIN 6
#define  BLUE_PIN  3

RGBLed led(RED_PIN, GREEN_PIN, BLUE_PIN, RGBLed::COMMON_ANODE); //  or RGBLed::COMMON_CATHODE

void setup()  {
  led.flash(RGBLed::RED, 200); // Interval 100ms
  led.flash(RGBLed::GREEN, 200); // Interval 100ms
  led.flash(RGBLed::BLUE, 200); // Interval 100ms
}

void loop()  {
  for (int i=0; i<255; ++i) {
    led.gradient(RGBLed::RED, RGBLed::GREEN, i); 
    delay(10);
  }
  for (int i=0; i<255; ++i) {
    led.gradient(RGBLed::GREEN, RGBLed::BLUE, i);
    delay(10);
  }
  for (int i=0; i<255; ++i) {
    led.gradient(RGBLed::BLUE, RGBLed::RED, i);
    delay(10);
  }
  for (int i=0; i<255; ++i) {
    led.gradient(RGBLed::RED, RGBLed::GREEN, i); 
    delay(10);
  }
  for (int i=0; i<255; ++i) {
    led.gradient(RGBLed::GREEN, RGBLed::BLUE, i);
    delay(10);
  }
  for (int i=0; i<255; ++i) {
    led.gradient(RGBLed::BLUE, RGBLed::RED, i);
    delay(10);
  }
}