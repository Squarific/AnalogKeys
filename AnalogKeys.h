/*
	AnalogKeys.h - Library for analog key managment for lcds (designed for LCD Keypad Shield V2.0)
	Created by Filip Smets, 22/05/2014.
	Released into the public domain.
*/

#ifndef AnalogKeys_h
#define AnalogKeys_h

#include "Arduino.h"
#include "LiquidCrystal.h"

class AnalogKeys {
	public:
		AnalogKeys(LiquidCrystal lcd, int pin, char* keylist, int keylistLength, int analogValues);
		char* getPressedKey();
		void calibrateKeys();
	private:
		LiquidCrystal _lcd;
		char* _keylist;
		int _pin;
		int _keylistLength;
		int _analogValues;
};

#endif