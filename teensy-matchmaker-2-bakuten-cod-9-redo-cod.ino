#include <Adafruit_Thermal.h>
#include <Arduino.h>
#include <Keypad.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(23, 22, 21, 20, 19, 18);  // LCD pins 4, 6, 11, 12, 13, 14

// BakuTen guys bmp header files
#include "bigmori.h"
#include "bobokun.h"
#include "bubusama.h"
#include "cindy.h"
#include "hijikata.h"
#include "kaishu.h"
#include "kattchan.h"
#include "mrblue.h"
#include "okita.h"
#include "ryoma.h"
#include "tomichan.h"
#include "tomomeanie.h"

// CoD guys bmp header files
#include "dia.h"
#include "fenn.h"
#include "grayson.h"
#include "guy.h"
#include "jasper.h"
#include "knight.h"
#include "lance.h"
#include "lou.h"
#include "lynt.h"
#include "rio.h"
#include "roy.h"
#include "tino.h"
#include "toa.h"

// Class MATCHSIGN to find the sign of user's match
#include "MATCHSIGN.h"

#define TX_PIN 10 // Arduino transmit GREEN WIRE labeled TX on printer
#define RX_PIN 9 // Arduino receive YELLOW WIRE labeled RX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {1, 2, 3, 4}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 6, 7, 8}; // Connect to the column pinouts of the keypad
String keyPressed, userMatchSign, gameMode, userBirthday;
int keyCount = 0;

// Create new instance with Keypad constructor called 'keypad'
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Use class MATCHSIGN with constructor
MATCHSIGN obj_aries("Leo", "Sag", "Aries", "Gemini", "Aquarius");
MATCHSIGN obj_taurus("Virgo", "Capricorn", "Taurus", "Cancer", "Pisces");
MATCHSIGN obj_gemini("Libra", "Aquarius", "Gemini", "Aries", "Leo");
MATCHSIGN obj_cancer("Scorpio", "Pisces", "Cancer", "Taurus", "Virgo");
MATCHSIGN obj_leo("Aries", "Sag", "Leo", "Gemini", "Libra");
MATCHSIGN obj_virgo("Taurus", "Capricorn", "Virgo", "Cancer", "Scorpio");
MATCHSIGN obj_libra("Gemini", "Aquarius", "Libra", "Leo", "Sag");
MATCHSIGN obj_scorpio("Cancer", "Pisces", "Scorpio", "Virgo", "Capricorn");
MATCHSIGN obj_sag("Aries", "Leo", "Sag", "Libra", "Aquarius");
MATCHSIGN obj_capricorn("Taurus", "Virgo", "Cancer", "Scorpio", "Pisces");
MATCHSIGN obj_aquarius("Gemini", "Libra", "Aquarius", "Aries", "Sag");
MATCHSIGN obj_pisces("Cancer", "Scorpio", "Pisces", "Taurus", "Capricorn");

// Class definition for BOY as per instructions on https://www.circuitxcode.com/creating-arduino-class/
class BOY {
  public:                        // Where the members are accessible (public - accessible from anywhere where the object is visible)
    String boy_name;             // Name of the boy
    const uint8_t* pic_name;     // Name of the bmp
    BOY (String n, const uint8_t* p) { // Class constructor
      boy_name = n;
      pic_name = p;
    }
    void printBoy(void) {        // Function (method) to thermal print bmp and name, and put printer to sleep
      Serial.println(boy_name);
      Serial.println(gameMode);
      Serial.println(userBirthday);
      printer.justify('C');      // Justify text on thermal printer
      printer.printBitmap(384, 384, pic_name);  // Thermal print bmp from header file
      printer.println();        // Print blank line
      printer.print("Your Birthday: "); // Print string
      printer.println(userBirthday); // Print birthday of user
      printer.print("Your Match: "); // Print string
      printer.println(boy_name); // Print name of boy
      printer.feed(3);          // Feed 3 lines to the printer
      printer.sleep();          // Tell printer to sleep
      delay(3000);              // Sleep for 3 seconds
      printer.wake();           // MUST wake() before printing again, even if reset
      printer.setDefault();     // Restore printer to defaults
    }
};

// Use class BOY with constructor
BOY obj_bigmori("Saigo Takamori", bigmori);
BOY obj_bobokun("Okubo Toshimichi", bobokun);
BOY obj_bubusama("Tokugawa Yoshinobu", bubusama);
BOY obj_cindy("Takasugi Shinsaku", cindy);
BOY obj_dia("Dia Akedia", dia);
BOY obj_fenn("Fenn Luxure", fenn);
BOY obj_grayson("Grayson Hotz", grayson);
BOY obj_guy("Guy Avari", guy);
BOY obj_hijikata("Hijikata Toshizo", hijikata);
BOY obj_jasper("Jasper Lane", jasper);
BOY obj_kaishu("Katsu Kaishu", kaishu);
BOY obj_kattchan("Katsura Kogoro", kattchan);
BOY obj_knight("Knight", knight);
BOY obj_lance("Lance Ira", lance);
BOY obj_lou("Lou", lou);
BOY obj_lynt("Lynt Akedia", lynt);
BOY obj_mrblue("Itagaki Taisuke", mrblue);
BOY obj_okita("Okita Souji", okita);
BOY obj_rio("Rio Voleri", rio);
BOY obj_roy("Roy Invidia", roy);
BOY obj_ryoma("Sakamoto Ryoma", ryoma);
BOY obj_tino("Tino Maes", tino);
BOY obj_toa("Toa Qelsum", toa);
BOY obj_tomichan("Sanjo Sanetomi", tomichan);
BOY obj_tomomeanie("Iwakura Tomomi", tomomeanie);

// Class definition for BOYJP
// Function as parameter in class object https://forum.arduino.cc/t/function-as-a-parameter-in-class-object-function-pointer-in-library/461967
class BOYJP {
    const uint8_t* pic_name;     // Name of the bmp
  public:                        // Where the members are accessible anywhere the object is visible
    BOYJP (void (*pointer)(), const uint8_t* p) { // Class constructor
      boyjp_name = pointer;
      pic_name = p;
    }
    void printBoyJP() {        // Function (method) to thermal print bmp and name, and put printer to sleep
      Serial.println(gameMode);
      Serial.println(userBirthday);

      findBdayIntJP();          // Run function to convert keyPressed into several ints
      printer.justify('C');      // Justify text on thermal printer
      printer.printBitmap(384, 384, pic_name);  // Thermal print bmp from header file
      printer.println();        // Print blank line
      printBirthdayJP();        // Run function to print 'your birthday' in Japanese
      printer.print(monthInt);  // Print month of user's birthday
      printMonthJP();           // Run function to print 'month' in Japanese
      printer.print(dayInt);    // Print day of user's birthday
      printDayJP();             // Run function to print 'day' in Japanese
      printKareJP();            // Run function to print 'your kare' in Japanese
      boyjp_name();             // Run function to print name of boy in Japanese
      printer.feed(3);          // Feed 3 lines to the printer
      printer.sleep();          // Tell printer to sleep
      delay(3000);              // Sleep for 3 seconds
      printer.wake();           // MUST wake() before printing again, even if reset
      printer.setDefault();     // Restore printer to defaults
    }
  private:
    void (*boyjp_name)();       // Function for name of the boy in Japanese
    int bdayInt;                // Declare variable for findBdayIntJP();
    int monthInt;               // Declare variable for findBdayIntJP();
    int dayInt;                 // Declare variable for findBdayIntJP();

    void printBirthdayJP() {          // Function to print 'your birthday' in Japanese
      printer.writeBytes(28, '&');    // FS &; Select Kanji character mode
      printer.writeBytes(27, 57);     // Select Chinese code format; ESC 9
      printer.writeBytes(0);          // 0: GBK code; https://www.khngai.com/chinese/charmap/tblgb.php
      printer.writeBytes(0xA5, 0xE6); // Katakana [yu]
      printer.writeBytes(0xA3, 0xAD); // Katakana [-]
      printer.writeBytes(0xA4, 0xCE); // Hiragana [no]
      printer.writeBytes(27, 57);     // Select Chinese code format; ESC 9
      printer.writeBytes(3);          // 3: BIG5 code; http://ash.jp/code/cn/big5tbl.htm
      printer.writeBytes(0xBD, 0xCF); // Kanji [tan]
      printer.writeBytes(0xA5, 0xCD); // Kanji [jou]
      printer.writeBytes(0xA4, 0xE9); // Kanji [bi]
      printer.writeBytes(28, '.');    // FS .; Cancel Kanji character mode
      printer.print(" : ");             // Print string with semi-colon
    }
    void printKareJP() {              // Function to print 'your kare' in Japanese
      printer.writeBytes(28, '&');    // FS &; Select Kanji character mode
      printer.writeBytes(27, 57);     // Select Chinese code format; ESC 9
      printer.writeBytes(0);          // 0: GBK code; https://www.khngai.com/chinese/charmap/tblgb.php
      printer.writeBytes(0xA5, 0xE6); // Katakana [yu]
      printer.writeBytes(0xA3, 0xAD); // Katakana [-]
      printer.writeBytes(0xA4, 0xCE); // Hiragana [no]
      printer.writeBytes(0xB1, 0xCB); // Kanji [kare]
      printer.writeBytes(28, '.');    // FS .; Cancel Kanji character mode
      printer.print(" : ");             // Print string with semi-colon
    }
    void printMonthJP() {
      printer.writeBytes(28, '&');    // FS &; Select Kanji character mode
      printer.writeBytes(27, 57);     // Select Chinese code format; ESC 9
      printer.writeBytes(1);          // 1: UTF-8 code; https://www.shabsin.com/~rshabsin/chineseutf8chars.html
      printer.writeBytes(0xE6, 0x9C, 0x88); // Kanji [tsuki]
      printer.writeBytes(28, '.');    // FS .; Cancel Kanji character mode
    }
    void printDayJP() {
      printer.writeBytes(28, '&');    // FS &; Select Kanji character mode
      printer.writeBytes(27, 57);     // Select Chinese code format; ESC 9
      printer.writeBytes(1);          // 1: UTF-8 code; https://www.shabsin.com/~rshabsin/chineseutf8chars.html
      printer.writeBytes(0xE6, 0x97, 0xA5); // Kanji [nichi]
      printer.writeBytes(28, '.');    // FS .; Cancel Kanji character mode
      printer.println();
    }
    void findBdayIntJP() {
      bdayInt = keyPressed.toInt(); // Convert String keyPressed into int
      monthInt = bdayInt / 100;     // Find the month by dividing by 100
      dayInt = bdayInt % 100;       // Find the day by using modulo 100

      Serial.println(bdayInt);
      Serial.println(monthInt);
      Serial.println(dayInt);
    }
};

// Declare functions to print names in Japanese so that they appear in scope for BOYJP objects
void bigmori_name();
void bobokun_name();
void bubusama_name();
void cindy_name();
void hijikata_name();
void kaishu_name();
void kattchan_name();
void mrblue_name();
void okita_name();
void ryoma_name();
void tomichan_name();
void tomomeanie_name();

// Use class BOYJP with constructor
BOYJP objjp_bigmori(bigmori_name, bigmori);
BOYJP objjp_bobokun(bobokun_name, bobokun);
BOYJP objjp_bubusama(bubusama_name, bubusama);
BOYJP objjp_cindy(cindy_name, cindy);
BOYJP objjp_hijikata(hijikata_name, hijikata);
BOYJP objjp_kaishu(kaishu_name, kaishu);
BOYJP objjp_kattchan(kattchan_name, kattchan);
BOYJP objjp_mrblue(mrblue_name, mrblue);
BOYJP objjp_okita(okita_name, okita);
BOYJP objjp_ryoma(ryoma_name, ryoma);
BOYJP objjp_tomichan(tomichan_name, tomichan);
BOYJP objjp_tomomeanie(tomomeanie_name, tomomeanie);

void setup() {
  Serial.begin(19200);
  Serial.println("Serial monitor is working! Hurray!");

  // Instructiuons to the user to select gameMode
  lcd.begin(16, 2);
  lcd.print("Press B for BT");
  lcd.setCursor(0, 1);
  lcd.print("Press C for CoD");

  mySerial.begin(19200);  // Initialize SoftwareSerial
  printer.begin();        // Initialize printer (same regardless of serial type)

  randomSeed(analogRead(A13)); // Initialize the random number generator with a random input such as analogRead() on an unconnected pin

  //  // Testing class BOY
  //  obj_dia.printBoy();
  //
  //  // Testing class BOYJP
  //  objjp_cindy.printBoyJP();
  //
  //  // Testing class MATCHSIGN
  //  String ariesMatch;
  //  ariesMatch = obj_aries.randomMatchSign();
  //  Serial.println(ariesMatch);
}


void loop() {
  char key = keypad.getKey(); // Set 'key' to whichever key is pressed

  if (key != NO_KEY) {
    Serial.println(key);      // Print 'key' to serial monitor

    // If 'B' is pressed, set gameMode to "BakuTen"
    if (key == 'B') {
      gameMode = "BakuTen";
      Serial.println(gameMode);
      lcd.begin(16, 2);               // Display text on LCD
      lcd.print("BakuTen Mode");
      delay(3000);
      lcd.begin(16, 2);               // Prompt user to enter birthday
      lcd.print("Enter birthdate");
      lcd.setCursor(0, 1);
      lcd.print("in MMDD format");
    }

    // If 'C' is pressed, set gameMode to "Court of Darkness"
    else if (key == 'C') {
      gameMode = "Court of Darkness";
      Serial.println(gameMode);
      lcd.begin(16, 2);               // Display text on LCD
      lcd.print("CoD Mode");
      delay(3000);
      lcd.begin(16, 2);               // Prompt user to enter birthday
      lcd.print("Enter birthdate");
      lcd.setCursor(0, 1);
      lcd.print("in MMDD format");
    }

    // If 'D' is pressed, set gameMode to "BakuTenJP"
    else if (key == 'D') {
      gameMode = "BakuTenJP";
      Serial.println(gameMode);
      lcd.begin(16, 2);               // Display text on LCD
      lcd.print("BakuTen JPN Mode");
      delay(3000);
      lcd.begin(16, 2);               // Prompt user to enter birthday
      lcd.print("Enter birthdate");
      lcd.setCursor(0, 1);
      lcd.print("in MMDD format");
    }

    // If # or * or A are pressed, tell user 'Not valid!'
    else if ((key == '#') || (key == '*') || (key == 'A')) {
      lcd.begin(16, 2);               // Display text on LCD
      lcd.print("Not valid!");
      delay(3000);
      lcd.begin(16, 2);               // Prompt user to enter birthday
      lcd.print("Enter birthdate");
      lcd.setCursor(0, 1);
      lcd.print("in MMDD format");
    }

    // If anything else is pressed, concatenate 'key' to string 'keyPressed'
    else {
      keyCount++;

      if (keyCount == 1) {
        lcd.clear();          // Clear the LCD of instructions
        lcd.print(key);       // Print the key to the LCD
        keyPressed += key;    // Concatenate 'key' to string keyPressed
      }

      else if (keyCount < 4) {
        lcd.print(key);                 // Print the key to the LCD
        keyPressed += key;              // Concatenate 'key' to string keyPressed
      }

      // If the length of String keyPressed is 4, run the following functions to print a match
      else if (keyCount == 4) {
        lcd.print(key);                 // Print the key to the LCD
        keyPressed += key;              // Concatenate 'key' to string keyPressed
        Serial.println(keyPressed);

        findBirthday();                 // Find the user's birthday based on keyPressed and return a string for the birthday
        findMatchSign();                // Find the sign of the user based on keyPressed and use that sign to find the sign of the user's match
        findMatchBoy();                 // Using the sign of the user's match, randomly select a boy to thermal print
        keyPressed = "";                // Clear the String keyPressed
        keyCount = 0;                   // Reset the int keyCount

        lcd.begin(16, 2);               // Prompt user to enter birthday
        lcd.print("Enter birthdate");
        lcd.setCursor(0, 1);
        lcd.print("in MMDD format");
      }

      else {
        lcd.begin(16, 2);               // Display text on LCD
        lcd.print("Not valid!");
        delay(3000);
        lcd.begin(16, 2);               // Prompt user to enter birthday
        lcd.print("Enter birthdate");
        lcd.setCursor(0, 1);
        lcd.print("in MMDD format");
      }

    }
  }
}

// Function that turns keyPressed into a string in "Month Day" format
String findBirthday() {
  int bdayInt, monthInt, dayInt;
  String monthString, dayString;
  bdayInt = keyPressed.toInt(); // Turn string 'keyPressed' to an int as 'bdayInt'
  monthInt = bdayInt / 100;     // Find the month by dividing by 100
  dayInt = bdayInt % 100;       // Find the day by using modulo 100
  dayString = String(dayInt);

  if (monthInt == 1) {
    monthString = "January";
  }

  else if (monthInt == 2) {
    monthString = "February";
  }

  else if (monthInt == 3) {
    monthString = "March";
  }

  else if (monthInt == 4) {
    monthString = "April";
  }

  else if (monthInt == 5) {
    monthString = "May";
  }

  else if (monthInt == 6) {
    monthString = "June";
  }

  else if (monthInt == 7) {
    monthString = "July";
  }

  else if (monthInt == 8) {
    monthString = "August";
  }

  else if (monthInt == 9) {
    monthString = "September";
  }

  else if (monthInt == 10) {
    monthString = "October";
  }

  else if (monthInt == 11) {
    monthString = "November";
  }

  else if (monthInt == 12) {
    monthString = "December";
  }

  userBirthday = monthString + " " + dayString;
  return userBirthday;
}

// Function that assigns string value to userMatchSign based on the int of keyPressed
String findMatchSign() {
  int bdayInt;
  bdayInt = keyPressed.toInt(); // Turn string 'keyPressed' to an int as 'bdayInt'

  // Aries
  if ((bdayInt >= 321 && bdayInt <= 331) || (bdayInt >= 401 && bdayInt <= 419)) {
    userMatchSign = obj_aries.randomMatchSign();
  }

  // Taurus
  else if ((bdayInt >= 420 && bdayInt <= 430) || (bdayInt >= 501 && bdayInt <= 520)) {
    userMatchSign = obj_taurus.randomMatchSign();
  }

  // Gemini
  else if ((bdayInt >= 521 && bdayInt <= 531) || (bdayInt >= 601 && bdayInt <= 620)) {
    userMatchSign = obj_gemini.randomMatchSign();
  }

  // Cancer
  else if ((bdayInt >= 621 && bdayInt <= 630) || (bdayInt >= 701 && bdayInt <= 722)) {
    userMatchSign = obj_cancer.randomMatchSign();
  }

  // Leo
  else if ((bdayInt >= 723 && bdayInt <= 731) || (bdayInt >= 801 && bdayInt <= 822)) {
    userMatchSign = obj_leo.randomMatchSign();
  }

  // Virgo
  else if ((bdayInt >= 823 && bdayInt <= 831) || (bdayInt >= 901 && bdayInt <= 922)) {
    userMatchSign = obj_virgo.randomMatchSign();
  }

  // Libra
  else if ((bdayInt >= 923 && bdayInt <= 930) || (bdayInt >= 1001 && bdayInt <= 1022)) {
    userMatchSign = obj_libra.randomMatchSign();
  }

  // Scorpio
  else if ((bdayInt >= 1023 && bdayInt <= 1031) || (bdayInt >= 1101 && bdayInt <= 1121)) {
    userMatchSign = obj_scorpio.randomMatchSign();
  }

  // Sag
  else if ((bdayInt >= 1122 && bdayInt <= 1130) || (bdayInt >= 1201 && bdayInt <= 1221)) {
    userMatchSign = obj_sag.randomMatchSign();
  }

  // Capricorn
  else if ((bdayInt >= 1222 && bdayInt <= 1231) || (bdayInt >= 101 && bdayInt <= 119)) {
    userMatchSign = obj_capricorn.randomMatchSign();
  }

  // Aquarius
  else if ((bdayInt >= 120 && bdayInt <= 131) || (bdayInt >= 201 && bdayInt <= 218)) {
    userMatchSign = obj_aquarius.randomMatchSign();
  }

  // Pisces
  else if ((bdayInt >= 219 && bdayInt <= 229) || (bdayInt >= 301 && bdayInt <= 320)) {
    userMatchSign = obj_pisces.randomMatchSign();
  }

  else {
    lcd.clear();
    lcd.print("   Not valid!");
    lcd.setCursor(0, 1);
    lcd.print("   Try again.");
    delay(3000);
    Serial.print("Not valid!");
  }

  Serial.println(userMatchSign);
  return userMatchSign;
}

// Function that finds match based on the value returned from findMatchSign() for userMatchSign
void findMatchBoy() {

  // If gameMode is BakuTen, select matches from BakuTen
  if (gameMode == "BakuTen") {
    if (userMatchSign == "Aries") {
      obj_mrblue.printBoy();
    }

    else if (userMatchSign == "Taurus") {
      obj_hijikata.printBoy();
    }

    else if (userMatchSign == "Gemini") {
      Serial.println("No Geminis!!");       // Replace Gemini with Aquarius
      obj_tomichan.printBoy();              // Aquarius
    }

    else if (userMatchSign == "Cancer") {
      int r = random(2);
      switch (r) {
        case 0:
          obj_kattchan.printBoy();
          break;
        case 1:
          obj_okita.printBoy();
          break;
      }
    }

    else if (userMatchSign == "Leo") {
      int r = random(2);
      switch (r) {
        case 0:
          obj_bobokun.printBoy();
          break;
        case 1:
          obj_cindy.printBoy();
          break;
      }
    }

    else if (userMatchSign == "Virgo") {
      obj_tomomeanie.printBoy();
    }

    else if (userMatchSign == "Libra") {
      Serial.println("No Libras!!");          // Replace Libra with Aquarius
      obj_tomichan.printBoy();                // Aquarius
    }

    else if (userMatchSign == "Scorpio") {
      int r = random(2);
      switch (r) {
        case 0:
          obj_bubusama.printBoy();
          break;
        case 1:
          obj_ryoma.printBoy();
          break;
      }
    }

    else if (userMatchSign == "Sag") {
      obj_bigmori.printBoy();
    }

    else if (userMatchSign == "Capricorn") {
      Serial.println("No Capricorns!!");      // Replace Capricorn with Taurus and Virgo
      int r = random(2);
      switch (r) {
        case 0:
          obj_hijikata.printBoy();            // Taurus
          break;
        case 1:
          obj_tomomeanie.printBoy();          // Virgo
          break;
      }
    }

    else if (userMatchSign == "Aquarius") {
      obj_tomichan.printBoy();
    }

    else if (userMatchSign == "Pisces") {
      obj_kaishu.printBoy();
    }
  }

  // If gameMode is Court of Darkness, select matches from Court of Darkness
  else if (gameMode == "Court of Darkness") {
    if (userMatchSign == "Aries") {
      obj_lance.printBoy();
    }

    else if (userMatchSign == "Taurus") {
      int r = random(2);
      switch (r) {
        case 0:
          obj_fenn.printBoy();
          break;
        case 1:
          obj_rio.printBoy();
          break;
      }
    }

    else if (userMatchSign == "Gemini") {
      Serial.println("No Geminis!!");       // Replace Gemini with Libra
      obj_tino.printBoy();                  // Libra
    }

    else if (userMatchSign == "Cancer") {
      int r = random(2);
      switch (r) {
        case 0:
          obj_lynt.printBoy();
          break;
        case 1:
          obj_toa.printBoy();
          break;
      }
    }

    else if (userMatchSign == "Leo") {
      obj_grayson.printBoy();
    }

    else if (userMatchSign == "Virgo") {
      obj_jasper.printBoy();
    }

    else if (userMatchSign == "Libra") {
      obj_tino.printBoy();
    }

    else if (userMatchSign == "Scorpio") {
      obj_guy.printBoy();
    }

    else if (userMatchSign == "Sag") {
      obj_dia.printBoy();
    }

    else if (userMatchSign == "Capricorn") {
      obj_lou.printBoy();
    }

    else if (userMatchSign == "Aquarius") {
      Serial.println("No Aquarius'!!");         // Replace Aquarius with Libra
      obj_tino.printBoy();                      // Libra
    }

    else if (userMatchSign == "Pisces") {
      int r = random(2);
      switch (r) {
        case 0:
          obj_knight.printBoy();
          break;
        case 1:
          obj_roy.printBoy();
          break;
      }
    }
  }

  // If gameMode is BakuTenJP, select matches from BakuTenJP
  else if (gameMode == "BakuTenJP") {
    if (userMatchSign == "Aries") {
      objjp_mrblue.printBoyJP();
    }

    else if (userMatchSign == "Taurus") {
      objjp_hijikata.printBoyJP();
    }

    else if (userMatchSign == "Gemini") {
      Serial.println("No Geminis!!");         // Replace Gemini with Aquarius
      objjp_tomichan.printBoyJP();            // Aquarius
    }

    else if (userMatchSign == "Cancer") {
      int r = random(2);
      switch (r) {
        case 0:
          objjp_kattchan.printBoyJP();
          break;
        case 1:
          objjp_okita.printBoyJP();
          break;
      }
    }

    else if (userMatchSign == "Leo") {
      int r = random(2);
      switch (r) {
        case 0:
          objjp_bobokun.printBoyJP();
          break;
        case 1:
          objjp_cindy.printBoyJP();
          break;
      }
    }

    else if (userMatchSign == "Virgo") {
      objjp_tomomeanie.printBoyJP();
    }

    else if (userMatchSign == "Libra") {
      Serial.println("No Libras!!");           // Replace Libra with Aquarius
      objjp_tomichan.printBoyJP();             // Aquarius
    }

    else if (userMatchSign == "Scorpio") {
      int r = random(2);
      switch (r) {
        case 0:
          objjp_bubusama.printBoyJP();
          break;
        case 1:
          objjp_ryoma.printBoyJP();
          break;
      }
    }

    else if (userMatchSign == "Sag") {
      objjp_bigmori.printBoyJP();
    }

    else if (userMatchSign == "Capricorn") {
      Serial.println("No Capricorns!!");      // Replace Capricorn with Taurus and Virgo
      int r = random(2);
      switch (r) {
        case 0:
          objjp_hijikata.printBoyJP();        // Taurus
          break;
        case 1:
          objjp_tomomeanie.printBoyJP();      // Virgo
          break;
      }
    }

    else if (userMatchSign == "Aquarius") {
      objjp_tomichan.printBoyJP();
    }

    else if (userMatchSign == "Pisces") {
      objjp_kaishu.printBoyJP();
    }
  }

  else {
    Serial.print("Choose game mode!");
    lcd.clear();
    lcd.print("Choose game mode!");
    delay(3000);
  }
}

// Printing Chinese as per https://leap.tardate.com/playground/thermalprinter/lucky4doracle/
// User manual for printer https://cdn-shop.adafruit.com/datasheets/CSN-A2+User+Manual.pdf

// Okubo Toshimichi in Japanese
void bobokun_name() {
  printer.writeBytes(28, '&');    // FS &; Select Kanji character mode
  printer.writeBytes(27, 57);     // Select Chinese code format; ESC 9
  printer.writeBytes(3);          // 3: BIG5 code; http://ash.jp/code/cn/big5tbl.htm
  printer.writeBytes(0xA4, 0x6A); // Kanji [oo]
  printer.writeBytes(0xA4, 0x5B); // Kanji [ku]
  printer.writeBytes(0xAB, 0x4F); // Kanji [bo]
  printer.writeBytes(0xA7, 0x51); // Kanji [toshi]
  printer.writeBytes(0xB3, 0x71); // Kanji [michi]
  printer.println();              // Print the bytes that were sent to writeBytes
  printer.writeBytes(28, '.');    // FS .; Cancel Kanji character mode
}

// Katsu Kaishu in Japanese
void kaishu_name() {
  printer.writeBytes(28, '&');    // FS &; Select Kanji character mode
  printer.writeBytes(27, 57);     // Select Chinese code format; ESC 9
  printer.writeBytes(3);          // 3: BIG5 code; http://ash.jp/code/cn/big5tbl.htm
  printer.writeBytes(0xB3, 0xD3); // Kanji [katsu]
  printer.writeBytes(0xAE, 0xFC); // Kanji [kai]
  printer.writeBytes(0xA6, 0xE0); // Kanji [shuu]
  printer.println();              // Print the bytes that were sent to writeBytes
  printer.writeBytes(28, '.');    // FS .; Cancel Kanji character mode
}

// Sakamoto Ryoma in Japanese
void ryoma_name() {
  printer.writeBytes(28, '&');    // FS &; Select Kanji character mode
  printer.writeBytes(27, 57);     // Select Chinese code format; ESC 9
  printer.writeBytes(0);          // 0: GBK code; https://www.khngai.com/chinese/charmap/tblgb.php
  printer.writeBytes(0xDB, 0xE0); // Kanji [saka]GBK
  printer.writeBytes(27, 57);     // Select Chinese code format; ESC 9
  printer.writeBytes(3);          // 3: BIG5 code; http://ash.jp/code/cn/big5tbl.htm
  printer.writeBytes(0xA5, 0xBB); // Kanji [moto]
  printer.writeBytes(0xC0, 0x73); // Kanji [ryo]
  printer.writeBytes(0xB0, 0xA8); // Kanji [ma]
  printer.println();              // Print the bytes that were sent to writeBytes
  printer.writeBytes(28, '.');    // FS .; Cancel Kanji character mode
}

// Takasugi Shinsaku in Japanese
void cindy_name() {
  printer.writeBytes(28, '&');    // FS &; Select Kanji character mode
  printer.writeBytes(27, 57);     // Select Chinese code format; ESC 9
  printer.writeBytes(3);          // 3: BIG5 code; http://ash.jp/code/cn/big5tbl.htm
  printer.writeBytes(0xB0, 0xAA); // Kanji [taka]
  printer.writeBytes(0xA7, 0xFC); // Kanji [sugi]
  printer.writeBytes(27, 57);     // Select Chinese code format; ESC 9
  printer.writeBytes(0);          // 0: GBK code; https://www.khngai.com/chinese/charmap/tblgb.php
  printer.writeBytes(0xBD, 0xFA); // Kanji [shin]GBK
  printer.writeBytes(27, 57);     // Select Chinese code format; ESC 9
  printer.writeBytes(3);          // 3: BIG5 code; http://ash.jp/code/cn/big5tbl.htm
  printer.writeBytes(0xA7, 0x40); // Kanji [saku]
  printer.println();              // Print the bytes that were sent to writeBytes
  printer.writeBytes(28, '.');    // FS .; Cancel Kanji character mode
}

// Tokugawa Yoshinobu in Japanese
void bubusama_name() {
  printer.writeBytes(28, '&');    // FS &; Select Kanji character mode
  printer.writeBytes(27, 57);     // Select Chinese code format; ESC 9
  printer.writeBytes(1);          // 1: UTF-8 code; https://www.shabsin.com/~rshabsin/chineseutf8chars.html
  printer.writeBytes(0xE5, 0xBE, 0xB3); // Kanji [toku]
  printer.writeBytes(0xE5, 0xB7, 0x9D); // Kanji [gawa]
  printer.writeBytes(0xE6, 0x85, 0xB6); // Kanji [yoshi]
  printer.writeBytes(0xE5, 0x96, 0x9C); // Kanji [nobu]
  printer.println();              // Print the bytes that were sent to writeBytes
  printer.writeBytes(28, '.');    // FS .; Cancel Kanji character mode
}

// Okita Souji in Japanese
void okita_name() {
  printer.writeBytes(28, '&');    // FS &; Select Kanji character mode
  printer.writeBytes(27, 57);     // Select Chinese code format; ESC 9
  printer.writeBytes(1);          // 1: UTF-8 code; https://www.shabsin.com/~rshabsin/chineseutf8chars.html
  printer.writeBytes(0xE6, 0xB2, 0X96); // Kanji [oki]
  printer.writeBytes(0xE7, 0x94, 0XB0); // Kanji [ta]
  printer.writeBytes(0xE7, 0xB7, 0x8F); // Kanji [sou]
  printer.writeBytes(0xE5, 0x8F, 0XB8); // Kanji [ji]
  printer.println();              // Print the bytes that were sent to writeBytes
  printer.writeBytes(28, '.');    // FS .; Cancel Kanji character mode
}

// Sanjo Sanetomi in Japanese
void tomichan_name() {
  printer.writeBytes(28, '&');    // FS &; Select Kanji character mode
  printer.writeBytes(27, 57);     // Select Chinese code format; ESC 9
  printer.writeBytes(1);          // 1: UTF-8 code; https://www.shabsin.com/~rshabsin/chineseutf8chars.html
  printer.writeBytes(0xE4, 0xB8, 0x89); // Kanji [san]
  printer.writeBytes(0xE6, 0x9D, 0xA1); // Kanji [jou]
  printer.writeBytes(0xE5, 0xAE, 0x9F); // Kanji [sane]
  printer.writeBytes(0xE7, 0xBE, 0x8E); // Kanji [tomi]
  printer.println();              // Print the bytes that were sent to writeBytes
  printer.writeBytes(28, '.');    // FS .; Cancel Kanji character mode
}

// Itagaki Taisuke in Japanese
void mrblue_name() {
  printer.writeBytes(28, '&');    // FS &; Select Kanji character mode
  printer.writeBytes(27, 57);     // Select Chinese code format; ESC 9
  printer.writeBytes(1);          // 1: UTF-8 code; https://www.shabsin.com/~rshabsin/chineseutf8chars.html
  printer.writeBytes(0xE6, 0x9D, 0xBF); // Kanji [ita]
  printer.writeBytes(0xE5, 0x9E, 0xA3); // Kanji [gaki]
  printer.writeBytes(0xE9, 0x80, 0x80); // Kanji [tai]
  printer.writeBytes(0xE5, 0x8A, 0xA9); // Kanji [suke]
  printer.println();              // Print the bytes that were sent to writeBytes
  printer.writeBytes(28, '.');    // FS .; Cancel Kanji character mode
}

// Katsura Kogoro in Japanese
void kattchan_name() {
  printer.writeBytes(28, '&');    // FS &; Select Kanji character mode
  printer.writeBytes(27, 57);     // Select Chinese code format; ESC 9
  printer.writeBytes(1);          // 1: UTF-8 code; https://www.shabsin.com/~rshabsin/chineseutf8chars.html
  printer.writeBytes(0xE6, 0xA1, 0x82); // Kanji [katsura]
  printer.writeBytes(0xE5, 0xB0, 0x8F); // Kanji [ko]
  printer.writeBytes(0xE4, 0xBA, 0x94); // Kanji [go]
  printer.writeBytes(0xE9, 0x83, 0x8E); // Kanji [rou]
  printer.println();              // Print the bytes that were sent to writeBytes
  printer.writeBytes(28, '.');    // FS .; Cancel Kanji character mode
}

// Saigo Takamori in Japanese
void bigmori_name() {
  printer.writeBytes(28, '&');    // FS &; Select Kanji character mode
  printer.writeBytes(27, 57);     // Select Chinese code format; ESC 9
  printer.writeBytes(1);          // 1: UTF-8 code; https://www.shabsin.com/~rshabsin/chineseutf8chars.html
  printer.writeBytes(0xE8, 0xA5, 0xBF); // Kanji [sai]
  printer.writeBytes(0xE9, 0x83, 0xB7); // Kanji [gou]
  printer.writeBytes(0xE9, 0x9A, 0x86); // Kanji [taka]
  printer.writeBytes(0xE7, 0x9B, 0x9B); // Kanji [mori]
  printer.println();              // Print the bytes that were sent to writeBytes
  printer.writeBytes(28, '.');    // FS .; Cancel Kanji character mode
}

// Hijikata Toshizo in Japanese
void hijikata_name() {
  printer.writeBytes(28, '&');    // FS &; Select Kanji character mode
  printer.writeBytes(27, 57);     // Select Chinese code format; ESC 9
  printer.writeBytes(1);          // 1: UTF-8 code; https://www.shabsin.com/~rshabsin/chineseutf8chars.html
  printer.writeBytes(0xE5, 0x9C, 0x9F); // Kanji [hiji]
  printer.writeBytes(0xE6, 0x96, 0xB9); // Kanji [kata]
  printer.writeBytes(0xE6, 0xAD, 0xB3); // Kanji [toshi]
  printer.writeBytes(0xE4, 0xB8, 0x89); // Kanji [zou]
  printer.println();              // Print the bytes that were sent to writeBytes
  printer.writeBytes(28, '.');    // FS .; Cancel Kanji character mode
}

// Iwakura Tomomi in Japanese
void tomomeanie_name() {
  printer.writeBytes(28, '&');    // FS &; Select Kanji character mode
  printer.writeBytes(27, 57);     // Select Chinese code format; ESC 9
  printer.writeBytes(1);          // 1: UTF-8 code; https://www.shabsin.com/~rshabsin/chineseutf8chars.html
  printer.writeBytes(0xE5, 0xB2, 0xA9); // Kanji [iwa]
  printer.writeBytes(0xE5, 0x80, 0x89); // Kanji [kura]
  printer.writeBytes(0xE5, 0x85, 0xB7); // Kanji [tomo]
  printer.writeBytes(0xE8, 0xA6, 0x96); // Kanji [mi]
  printer.println();              // Print the bytes that were sent to writeBytes
  printer.writeBytes(28, '.');    // FS .; Cancel Kanji character mode
}
