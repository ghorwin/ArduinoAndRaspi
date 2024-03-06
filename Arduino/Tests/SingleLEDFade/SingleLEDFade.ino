/*
  Fade

  This example shows how to fade an LED on pin 9 using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
  are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Fade
*/

int ledNr[3] = { 9, 11, 10 };
int brightness[3] = { 0, 80, 160 };
int fadeAmount[3] = { 5, 5, 5 };  // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  for (int i = 0; i < 3; ++i)
    pinMode(ledNr[i], OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness:
  for (int i = 0; i < 3; ++i) {
    analogWrite(ledNr[i], brightness[i]);

    // change the brightness for next time through the loop:
    if (brightness[i] > 200)
      brightness[i] = brightness[i] + 2 * fadeAmount[i];
    else
      brightness[i] = brightness[i] + fadeAmount[i];

    // reverse the direction of the fading at the ends of the fade:
    if (brightness[i] <= 0 || brightness[i] >= 255) {
      fadeAmount[i] = -fadeAmount[i];
    }
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}
