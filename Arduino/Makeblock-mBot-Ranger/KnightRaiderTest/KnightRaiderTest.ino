/* Testprogramm für den LED Ring auf dem Auriga Board. */

// Zuerst den Header für das Auriga-Board einbinden
#include <MeAuriga.h>

/*! Immer, wenn die Funktion step() aufgerufen wird, 
    werden die letzten x LEDs etwas abgedunkelt (die letzte immer aus) 
    und die nächste RGB LED erhält die gewünschte Farbe.
*/
class KnightRaiderLEDs {
public:
  void setup();

  void step(bool links, uint8_t red, uint8_t green, uint8_t blue);
 

  // Der Auriga on-board LED Ring hat 12 LEDs. Zur Vereinfachung der Lesbarkeit
  // legen wir hier ein Define fest.
  #define LEDNUM  12

  // Beim Auriga-Board steuern wird den on-board LED Ring an, 
  // welcher über Port 0 (PORT0, onboard) angesteuert wird.
  // Die Klasse MeRGBLed bietet die Schnittstellenfunktionen dafür.
  MeRGBLed led( PORT0, LEDNUM );

  // Anzahl der hinterherschleifenden LEDs
  #define TRAILING_LED_DISTANCE 6

  cRGB trailingLEDS[TRAILING_LED_DISTANCE];

};

KnightRaiderLEDs::setup() {
  // LED Ring Controller ist am PWM PIN D44 angeschlossen
  led.setpin( 44 );
  // Nach dem Setzen des Pin muss minimal kurz gewartet werden.
  // Wenn man den delay()-Aufruf vergisst, dann wird nach dem 
  // led.show() Befehl die erste LED in grün angezeigt.
  delay(1);
  // nun können wir die initalen LED-Werte (alle AUS/SCHWARZ) setzen
  led.show();
}


KnightRaiderLEDs leds;


void setup() {
  leds.setup();
}


void loop() {
  // wir setzen nun unterschiedliche Farben in den LEDs und schalten diese dann jeweils an
  for (uint8_t i = 0; i < LEDNUM; ++i ) 
     led.setColorAt( i, i*20, 210-i*20, i*10 ); // i = 0...11
  led.show();
  delay(1000);
  // alle LED wieder ausschalten
  led.setColor(0,0,0);
  led.show();
  delay(1000);
}
