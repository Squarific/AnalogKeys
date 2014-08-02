/*
	AnalogKeys.cpp - Library for analog key managment for lcds (designed for LCD Keypad Shield V2.0)
	Created by Filip Smets, 22/05/2014.
	Released into the public domain.
*/

#include "Arduino.h"
#include "AnalogKeys.h"
#include "LiquidCrystal.h"

AnalogKeys::AnalogKeys(LiquidCrystal lcd, int pin, char* keylist, int keylistLength, int analogValues) {
	_lcd = lcd;
	_pin = pin;
	_keylist = keylist;
	_keylistLength = keylistLength;
	_analogValues = analogValues;
}

char* AnalogKeys::getPressedKey() {
	int analogValue = analogRead(_pin);
    int currentKey = 0;
    int currentDifference = 0;
    for (int key = 0; key < _keylistLength; key++) {
        if (key == 0) {
            currentDifference = _analogValues[key] - analogValue;
            currentDifference = abs(currentDifference); //Math has to be kept out of abs() according to reference
        } else {
            int thisDifference = _analogValues[key] - analogValue;
            thisDifference = abs(thisDifference);
            if (thisDifference < currentDifference) {
                currentKey = key;
                currentDifference = thisDifference;
            }
        }
    }
    return currentKey;
}

void AnalogKeys::calibrateKeys (tryAmount, timePerKey) {
	int calsleep = timePerKey / tryAmount;
	for (int key = 0; key < _keylistLength; key++) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Calibrating keys");
        lcd.setCursor(0, 1);
        lcd.print("Press key ");
        lcd.print(_keylist[key]);
        delay(1000);
        long average = 0;
        for (int tries = 0; tries < tryAmount; tries++) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Calibrating keys");
            lcd.setCursor(0, 1);
            int currentKeyValue = analogRead(_pin);
            lcd.print(currentKeyValue);
            average += currentKeyValue;
            delay(calsleep);
        }
        _analogValues[key] = int(average / tryAmount);
    }
}