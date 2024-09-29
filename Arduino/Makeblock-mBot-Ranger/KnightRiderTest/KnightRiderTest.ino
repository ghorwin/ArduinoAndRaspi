/* Testprogramm für den LED Ring auf dem Auriga Board. */

#include <MeAuriga.h>

// Der Auriga on-board LED Ring hat 12 LEDs. Zur Vereinfachung der Lesbarkeit
// legen wir hier ein Define fest.
#define LEDNUM 12

/*! Immer, wenn die Funktion step() aufgerufen wird, 
    werden die letzten x LEDs etwas abgedunkelt (die letzte immer aus) 
    und die nächste RGB LED erhält die gewünschte Farbe.
*/
class KnightRiderLEDs {
public:
  /*! Constructor, takes optional number of trailing LEDs (max 12). */
  KnightRiderLEDs(uint8_t trailingLedCount = 6);

  void setup();

  /*! Alle LEDs ausschalten */
  void turnOff();

  /*! Steps one RGB forward (either clockwise or anti-clockwise direction), sets it to the new rgb value and dims the last 6 LEDs a bit. */
  void step(bool clockWise, uint8_t red, uint8_t green, uint8_t blue);

  // Beim Auriga-Board steuern wird den on-board LED Ring an,
  // welcher über Port 0 (PORT0, onboard) angesteuert wird.
  // Die Klasse MeRGBLed bietet die Schnittstellenfunktionen dafür.
  MeRGBLed    m_led;

  uint8_t     m_trailingLedCount;
  /*! The current (brightest) LED. */
  uint8_t     m_currentPos = 8; // topmost LED

  /*! Holds info on last LED. */
  struct LastLED {
    cRGB rgb;
    uint8_t index;
  };

  // holds history of last shown LEDs
  LastLED        m_trailingLEDS[LEDNUM];
};

// *** Implementierung der Klasse KnightRiderLEDs ***

KnightRiderLEDs::KnightRiderLEDs(uint8_t trailingLedCount) : 
  m_led(PORT0, LEDNUM)
{
  if (trailingLedCount > LEDNUM)
    m_trailingLedCount = LEDNUM;
  else 
    m_trailingLedCount = max(1, trailingLedCount);
}

void KnightRiderLEDs::setup() {
  // LED Ring Controller ist am PWM PIN D44 angeschlossen
  m_led.setpin(44);
  // Nach dem Setzen des Pin muss minimal kurz gewartet werden.
  // Wenn man den delay()-Aufruf vergisst, dann wird nach dem
  // led.show() Befehl die erste LED in grün angezeigt.
  delay(1);
  // nun können wir die initalen LED-Werte (alle AUS/SCHWARZ) setzen
  m_led.show();

  for (int i = 0; i < m_trailingLedCount; ++i) {
    m_led.setColorAt(i, 0,0,0); // Mind use of setColorAt() which uses zero-based indexing
  }
}

void KnightRiderLEDs::turnOff() {
  m_led.setColor(0, 0, 0, 0);  // all LEDs off
  m_led.show();
}

void KnightRiderLEDs::step(bool clockWise, uint8_t red, uint8_t green, uint8_t blue) {
  if (clockWise)
    m_currentPos = (m_currentPos + 1) % LEDNUM;   // Modulo 12 ->  (11 + 1) = 12  -> 12 % 12 = 0
  else
    m_currentPos = (m_currentPos + LEDNUM - 1) % LEDNUM;   // Modulo 12 ->  (0 + 11) = 12  -> 11 % 12 = 11
  
  // shift and dim trailing leds
  for (int i=m_trailingLedCount-1; i>0; --i) {
    // move LEDs one position forward
    m_trailingLEDS[i] = m_trailingLEDS[i-1];
  }

  // last trailing LED will be turned off
  m_trailingLEDS[m_trailingLedCount-1].rgb.r = 0;
  m_trailingLEDS[m_trailingLedCount-1].rgb.g = 0;
  m_trailingLEDS[m_trailingLedCount-1].rgb.b = 0;

  // set current led
  m_trailingLEDS[0].rgb.r = red;
  m_trailingLEDS[0].rgb.g = green;
  m_trailingLEDS[0].rgb.b = blue;
  m_trailingLEDS[0].index = m_currentPos;

  // now update the colors in the LED positions, but back to front in case we have direction reversal
  for (int i=m_trailingLedCount-1; i>=0; --i) {
    // compute dim factor
    // i = 0                     -> dim = 1
    // i = m_trailingLedCount-1  -> dim = 0
    // 
    float dim = float(m_trailingLedCount - 1.0 - i)/(m_trailingLedCount - 1);
    // we have to dim a bit more progressively towards low values
    dim = dim*dim;
    m_led.setColorAt(m_trailingLEDS[i].index, dim*m_trailingLEDS[i].rgb.r, dim*m_trailingLEDS[i].rgb.g, dim*m_trailingLEDS[i].rgb.b);
    // Serial.print(m_trailingLEDS[i].index);
    // Serial.print(";");
    // Serial.print(m_trailingLEDS[i].rgb.r);
    // Serial.print(";");
    // Serial.print(m_trailingLEDS[i].rgb.g);
    // Serial.print(";");
    // Serial.println(m_trailingLEDS[i].rgb.b);
  }

  m_led.show();
}

KnightRiderLEDs leds(9);

void setup() {
  leds.setup();
  Serial.begin(115200);
}


void loop() {
  // 4 times knight rider
  for (int i=0; i<12; ++i) {
    leds.step(true, 255,0,0);
    delay(100);
  }
  for (int i=0; i<12; ++i) {
    leds.step(false, 255,0,0);
    delay(100);
  }
  for (int i=0; i<12; ++i) {
    leds.step(true, 255,0,0);
    delay(100);
  }
  for (int i=0; i<12; ++i) {
    leds.step(false, 255,0,0);
    delay(100);
  }
  // now the color loop
  for (int i=0;i<16; ++i) {
    if ( (i & 0x7) == 0)
      continue;
    // color bits
    bool r = i & 0x1;
    bool g = i & 0x2;
    bool b = i & 0x4;
    for (int i=0; i<12; ++i) {
      leds.step(true, r*255,g*255,b*255);
      delay(100);
    }

  }
}
