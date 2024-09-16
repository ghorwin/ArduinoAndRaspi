/* 
  Beispielprogramm für eine LED RGB mit "Common Anode", 
  d.h. Anschluss von +5V an den längsten Fuß der RGB LED.

  Verwendet wird die Bibliothek RGB von WILMOUTH Steven

  HIGH an einem der RGB Pins heißt "aus".
*/

#include <RGBLed.h>
#include <RGB2HSV.h>


#define  RED_PIN   5
#define  GREEN_PIN 6
#define  BLUE_PIN  3

RGBLed led(RED_PIN, GREEN_PIN, BLUE_PIN, RGBLed::COMMON_ANODE); //  or RGBLed::COMMON_CATHODE

void setup()  {
  Serial.begin(115200);
  led.flash(RGBLed::RED, 200); // Interval 100ms
  led.flash(RGBLed::GREEN, 200); // Interval 100ms
  led.flash(RGBLed::BLUE, 200); // Interval 100ms

    unsigned char h = 172;
  RgbColor rgb = HsvToRgb( HsvColor(h,255,255) );
  led.setColor(rgb.m_r, rgb.m_g, rgb.m_b);
  Serial.print("h:");
  Serial.print(h);
  Serial.print(",r:");
  Serial.print(rgb.m_r);
  Serial.print(",g:");
  Serial.print(rgb.m_g);
  Serial.print(",b:");
  Serial.println(rgb.m_b);

}

void loop()  {
#if 0
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
#endif

  for (int i=0;i<256; ++i) {
    RgbColor rgb = HsvToRgb( HsvColor(i,255,255) );
    // compute relative value
    // unsigned int value = (0.8*rgb.m_r + rgb.m_g + rgb.m_b)/(2.8*256.)*256;
    // Serial.print("rgb:");
    // Serial.print(0.8*rgb.m_r + rgb.m_g + rgb.m_b);
    // Serial.print("value:");
    // Serial.println(value);
    // rgb = HsvToRgb( HsvColor(i,255,value) );
    led.setColor(rgb.m_r, rgb.m_g, rgb.m_b);
    #if 0
    Serial.print("h:");
    Serial.print(i);
    Serial.print(",r:");
    Serial.print(rgb.m_r);
    Serial.print(",g:");
    Serial.print(rgb.m_g);
    Serial.print(",b:");
    Serial.println(rgb.m_b);
    #endif
    delay(15);
  }

}