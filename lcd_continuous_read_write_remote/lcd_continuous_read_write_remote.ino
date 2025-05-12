#include <LiquidCrystal.h>
#include <IRremote.hpp>
#include <dht.h>

#define LCD_RS 12
#define LCD_EN 11
#define LCD_D4 5
#define LCD_D5 4
#define LCD_D6 3
#define LCD_D7 2

#define DHT_PIN 50

dht DHT;
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
IRrecv IR(7);

byte current_selection = 0;

void setup() {
  lcd.begin(16, 2);
  IR.enableIRIn();

  lcd.print("Waiting for command");
}

void loop() {
  bool isCommandWritten = false;
  if (IR.decode()) {
    lcd.clear();
    lcd.print("decoded!");
    delay(500);
    byte input_from_remote = decode_hex_code(IR.decodedIRData.decodedRawData);
    if (input_from_remote == 0 && current_selection != 0) {
      isCommandWritten = true;
      write_command(current_selection);
      return;
    }
    write_command(input_from_remote);
    IR.resume();
  }
  if (current_selection != 0 && isCommandWritten == false) {
    write_command(current_selection);
  }
}

byte decode_hex_code(unsigned long hexCode) {
  lcd.clear();
  lcd.print("reading..");
  delay(500);
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

void write_command(byte input) {
  current_selection = input;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Input from remote was: ");
  lcd.setCursor(0, 1);
  int chk = -1;
  if (input == 1) {
    chk = DHT.read11(DHT_PIN);
    
    lcd.print("temp: ");
    lcd.print(DHT.temperature);
    delay(500);
  } else if (input == 2) {
    chk = DHT.read11(DHT_PIN);
    
    lcd.print("humidity: ");
    lcd.print(DHT.humidity);
    delay(500);
  } 
  if (input == 0) {
    lcd.print("try again");
  } else {
    lcd.print(current_selection);
    delay(500);
  }
}