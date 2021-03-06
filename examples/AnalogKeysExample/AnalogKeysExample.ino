/*
	AnalogKeys example file - Library for analog key managment for lcds (designed for LCD Keypad Shield V2.0)
	Created by Filip Smets, 22/05/2014.
	Released into the public domain.

        Note: Before you start using this library, make sure you understand how the lcd works!
*/

#include <LiquidCrystal.h>
#include <AnalogKeys.h>

// LCD variables
#define rs 8
#define enable 9
#define d4 4
#define d5 5
#define d6 6
#define d7 7

LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);

//AnalogKey Variables
#define KEYSLENGTH (sizeof(keys) / sizeof(char *))
#define TRIES 40 // Number of times analog data is read while calibrating
#define CALIBRATIONTIME 800 // Nmber of ms each key takes to calibrate
#define TIMEPERKEY (CALIBRATIONTIME / TRIES)
#define INPUTPIN 0

char* keys [] = {"NONE", "LEFT", "RIGHT", "UP", "DOWN", "SELECT"};
int analogValues [KEYSLENGTH] = {}; // If you know the values of the keys you can already pass them, that way you don't have to calibrate
// Example with preprogrammed analog values:
// int analogValues [] = {675, 314, 0, 85, 475};

AnalogKeys analogKeys(&lcd, INPUTPIN, keys, KEYSLENGTH, analogValues);

boolean needsCalibration = true;

void setup () {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Calibrating keys...");
  needsCalibration = true;
}

void loop () {
   if (needsCalibration) {
       analogKeys.calibrateKeys(TRIES, TIMEPERKEY);
       needsCalibration = false;
   }
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Press a key");
   lcd.setCursor(0, 1);
   lcd.print("Pressed: ");
   lcd.print(analogKeys.getPressedKey());
   delay(200);
}
