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
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4); // Change to (0x27,20,4) for 20x4 LCD.

uint8_t cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};

int count;

void setup() {
  // Initiate the LCD:
  lcd.init();
  lcd.backlight();
  lcd.createChar(6, cross);
  count = 1;
}

void loop() {
  ++count;
  // Print 'Hello World!' on the first line of the LCD:
  lcd.setCursor(2, 0); // Set the cursor on the third column and first row.
  lcd.print("Moin Henrik"); // Print the string "Hello World!"
  delay(100);
  lcd.setCursor(2, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
  lcd.print("x");
  lcd.setCursor(3, 1); 
  lcd.print(count);
  delay(2000);
  lcd.clear();
  delay(1000);
}
