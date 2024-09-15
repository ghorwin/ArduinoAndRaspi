/* I2C LCD with Arduino example code. More info: https://www.makerguides.com */

// Include the libraries:
// LiquidCrystal_I2C.h: https://github.com/johnrickman/LiquidCrystal_I2C
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args) write(args);
#else
#define printByte(args) print(args,BYTE);
#endif

// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
//LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

uint8_t cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};

int count;

void setup() {
  // Initiate the LCD:
  lcd.init();
  lcd.backlight();
//  lcd.createChar(6, cross);
  lcd.clear();
}

void loop() {

  if (count >= 32)
    count = 0;
  int row = count / 16;
  int col = count % 16;

  lcd.setCursor(col,row); // Set the cursor on the third column and first row.
  // lcd.print(" ");

  ++count;
  lcd.print(col);
  delay(400);
}
