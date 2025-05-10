#include <LiquidCrystal.h>
#include <IRremote.hpp>

#define LCD_RS 12
#define LCD_EN 11
#define LCD_D4 5
#define LCD_D5 4
#define LCD_D6 3
#define LCD_D7 2

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
IRrecv IR(7);

void setup() {
  lcd.begin(16, 2);
  IR.enableIRIn();
  
  lcd.print("Waiting for command");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (IR.decode()) {
    
    byte input_from_remote = decode_hex_code(IR.decodedIRData.decodedRawData);

    write_command(input_from_remote);
    IR.resume();
  }
}

byte decode_hex_code(unsigned long hexCode) {
  switch (hexCode) {
    case 0xF30CFF00:
      return 1;
    case 0xE718FF00:
      return 2;
    case 0xA15EFF00:
      return 3;
    case 0xF708FF00:
      return 4;
    case 0xE31CFF00:
      return 5;
    case 0xA55AFF00:
      return 6;
    case 0xBD42FF00:
      return 7;
    default:
      return 0;
  }
}

void write_command (byte input_from_remote) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Input from remote was: ");
  lcd.setCursor(0, 1);
  if (input_from_remote == 0) {
    lcd.print("try again");
  } else {
    lcd.print(input_from_remote);
  }
}