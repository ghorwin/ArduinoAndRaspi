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
  Serial.println("Flash red, green, blue");
  // LED in den drei Grundfarben blinken lassen
  led.flash(RGBLed::RED, 400); // Interval 100ms
  led.flash(RGBLed::GREEN, 400); // Interval 100ms
  led.flash(RGBLed::BLUE, 400); // Interval 100ms
  delay(1000);
  // Umrechnung von Farbdefinition nach HSV auf RGB
  unsigned char h = 172; // hue - Wert
  RgbColor rgb = HsvToRgb( HsvColor(h,255,255) );
  Serial.print("HSV - RGB: h:");
  Serial.print(h);
  Serial.print(",r:");
  Serial.print(rgb.m_r);
  Serial.print(",g:");
  Serial.print(rgb.m_g);
  Serial.print(",b:");
  Serial.println(rgb.m_b);
  // LED Farbe ändern
  led.setColor(rgb.m_r, rgb.m_g, rgb.m_b);
  // und ausblenden
  led.fadeOut(rgb.m_r, rgb.m_g, rgb.m_b,50,500); // LED ausblenden
  delay(1000);
}

void loop()  {
  Serial.println("Alle Farben");
  // LED::gradient(startwert[],endwert[],step)
  //
  // Zuerst die Farben durchgehen, jeweils Farbwechsel von einer RGB Grundfarbe zur nächsten
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
  delay(1000);

  Serial.println("Ausblenden");
  // wieder ausblenden
  // LED::fadeout(r,g,b,steps,duration)
  // LED::fadeout(rgb[],steps,duration)
  led.fadeOut(RGBLed::RED, 50, 500);
  delay(1000);

  Serial.println("crossFade");
  // das gleiche nochmal mit LED::crossFade(startwert[],endwert[],step,duration)
  led.crossFade(RGBLed::RED, RGBLed::GREEN, 255, 2000); 
  led.crossFade(RGBLed::GREEN, RGBLed::BLUE, 255, 2000); 
  led.crossFade(RGBLed::BLUE, RGBLed::RED, 255, 2000); 

  // wieder ausblenden
  // LED::fadeout(r,g,b,steps,duration)
  // LED::fadeout(rgb[],steps,duration)
  led.fadeOut(RGBLed::RED, 50, 500);
  delay(1000);

  Serial.println("Farbrad (5mal)");
  // Farbrad
  for (int count=0; count<5; ++count) {
    for (int i=0;i<256; ++i) {
      // HSV zu RGB Konvertierung
      RgbColor rgb = HsvToRgb( HsvColor(i,255,255) );
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
}