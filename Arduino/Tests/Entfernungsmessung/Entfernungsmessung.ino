#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Library for LCD

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args) write(args);
#else
#define printByte(args) print(args,BYTE);
#endif

// *** Globals ***

byte  mode; // operating mode

// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4); 
// (0x27,20,4) for 20x4 LCD.
// (0x27,16,2) for 16x2 LCD.

// *** Pins ***

byte PIN_rangeTrig = 8;
byte PIN_rangeEcho = 7;


int scan_i2c() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    Wire.beginTransmission(address + 1);

    if (error == 0 && Wire.endTransmission() != 0)  // Special flag for SAMD Series
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("!");

      nDevices++;
      return address;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
      return address;
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
  return -1;
}



void setup() {
  byte  i2c_lcd_address;

  // initialize i2c library
  Wire.begin();

  // Debug output on serial monitor
  Serial.begin(9600);

  while (!Serial);  // Wait for serial monitor
  Serial.println("---Starting initialization---");

  // determine i2c address 
  i2c_lcd_address = scan_i2c();

  if (i2c_lcd_address != -1) {
    // Initiate the LCD:
    lcd.init();
    lcd.backlight();
    // write welcome text
    lcd.setCursor(0, 0); 
    lcd.print("Murmelbahn-Fahrstuhl");
    lcd.setCursor(0, 1); 
    lcd.print("Version 1.0");
    lcd.setCursor(0, 3); 
    //lcd.print("...warte auf Signal");
    mode = 0;
  }
  else 
    mode = -1;

  // pins

  pinMode(PIN_rangeTrig, OUTPUT); 
  pinMode(PIN_rangeEcho, INPUT); 

  digitalWrite(PIN_rangeTrig, LOW); // sets the trigger pin to low
}


void loop() {
  int duration;
  float distance; // radar distance in mm
  char distStr[10];
  // in Schleife 

  if (mode == 0) {
    // scan distance

    // send 10 µs trigger to high
    digitalWrite(PIN_rangeTrig, HIGH); // sets the trigger pin to low
    delayMicroseconds(12);
    digitalWrite(PIN_rangeTrig, LOW); // sets the trigger pin to low
    // wait for echo pin to be pulled up
    duration = pulseIn(PIN_rangeEcho, HIGH);
    // compute distance, signal travels 2*s distance in 'duration', with sound speed = 340m/s 
    distance = (float)duration * 340.0 / 2.0 / 1000.0; // calculate distance s=t*v_air/2 and convert from micro meters to mm 
    Serial.println(distance);
    sprintf(distStr, "%3d mm", (int)distance);
    lcd.setCursor(0, 3); 
    lcd.print(distStr);
    delay(1000);
  }
}
