#include <LiquidCrystal.h>
#include <dht.h>
#include <Keypad.h>
#include <string.h>

#define LCD_RS 12
#define LCD_EN 11
#define LCD_D4 5
#define LCD_D5 4
#define LCD_D6 3
#define LCD_D7 2

#define DHT_PIN 50

// K -> keypad, R -> row, C -> column
#define RK_5 45 
#define RK_6 43 
#define RK_7 41 
#define RK_8 39 
#define CK_1 37 
#define CK_2 35 
#define CK_3 33 
#define CK_4 31 

#define ROWS 4
#define COLS 4

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {RK_5, RK_6, RK_7, RK_8}; 
byte colPins[COLS] = {CK_1, CK_2, CK_3, CK_4};

Keypad keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

dht DHT;
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
byte current_selection = 0;

void setup() {
  lcd.begin(16, 2);

  lcd.print("Waiting for command");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    lcd.clear();
    byte input = decode_symbol(key);
    choose_selection(input);
  }

  if (current_selection != 0) {
    print_selection();
  }
}

byte decode_symbol(char symbol) {
  switch (symbol) {
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    default: return 0;
  }
}

void choose_selection(byte input) {
  current_selection = input;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DHT input: ");
}

void print_selection() {
  int chk = DHT.read11(DHT_PIN);
  if (current_selection == 1) {
    lcd.setCursor(0, 1);
    lcd.print("                "); 
    lcd.setCursor(0, 1);
    lcd.print("temp: ");
    lcd.print(DHT.temperature);
  } else if (current_selection == 2) {
    lcd.setCursor(0, 1);
    lcd.print("                "); 
    lcd.setCursor(0, 1);
    lcd.print("humidity: ");
    lcd.print(DHT.humidity); 
  }

  delay(500);

}