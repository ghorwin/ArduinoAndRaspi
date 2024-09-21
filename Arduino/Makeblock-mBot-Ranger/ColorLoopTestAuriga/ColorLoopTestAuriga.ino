/* Testprogramm für den LED Ring auf dem Auriga Board.
 */
#include <MeAuriga.h>

#define ALLLEDS        0

#ifdef MeAuriga_H

// Auriga on-board light ring has 12 LEDs
#define LEDNUM  12

// on-board LED ring, at PORT0 (onboard)
MeRGBLed led( 0, LEDNUM );

#else

#define LEDNUM  14

// external device
MeRGBLed led( PORT_3 );

#endif


float j, f, k;

void setup()
{
#ifdef MeAuriga_H
    // LED Ring controller is on Auriga D44/PWM
    led.setpin( 44 );
#endif
}

void loop()
{
  // color_loop();

  for (uint8_t i = 0; i < LEDNUM; ++i ) {
     led.setColorAt( i, 128, 0, 0 );
     led.show();
     delay(500);
  }
  for (uint8_t i = 0; i < LEDNUM; ++i ) {
     led.setColorAt( i, 0, 0, 0 );
     led.show();
     delay(500);
  }
  // led.show();

  // for (uint8_t t = 0; t < LEDNUM; t++ ) {
  //   uint8_t red	= 128;
  //   uint8_t green = 0;
  //   uint8_t blue = 0;
  //   led.setColorAt( t, red, green, blue );
  //   led.show();
  //   delay(500);
  // }
  // delay(1000);
  // for (uint8_t t = 0; t < LEDNUM; t++ ) {
  //   uint8_t red	= 0;
  //   uint8_t green = 128;
  //   uint8_t blue = 0;
  //   led.setColorAt( t, red, green, blue );
  //   led.show();
  //   delay(500);
  // }
  // delay(1000);

}


void color_loop()
{
  for (uint8_t t = 0; t < LEDNUM; t++ )
  {
    uint8_t red	= 64 * (1 + sin(t / 2.0 + j / 4.0) );
    uint8_t green = 64 * (1 + sin(t / 1.0 + f / 9.0 + 2.1) );
    uint8_t blue = 64 * (1 + sin(t / 3.0 + k / 14.0 + 4.2) );
    led.setColorAt( t, red, green, blue );
  }
  led.show();

  j += random(1, 6) / 6.0;
  f += random(1, 6) / 6.0;
  k += random(1, 6) / 6.0;
}

