#include "LiquidSkjerm.h"

// Konstruktør
LiquidSkjerm::LiquidSkjerm(int pinRS, int pinEN, int pinD4, int pinD5, int pinD6, int pinD7, 
                           int nRows, int nColm, String nName)
    : numColm(nColm), numRows(nRows), name(nName),
    lcd(pinRS, pinEN, pinD4, pinD5, pinD6, pinD7)

{
    // 1. Alloker minne for LiquidCrystal-objektet (pekeren 'lcd')
    // Her initialiseres LiquidCrystal-bibliotekets objekt med pinnene
    
}

// Initialiserer skjermen (kaller LiquidCrystal::begin)
void LiquidSkjerm::begin() {
    // 2. Kall LiquidCrystal-objektets begin() metode med størrelsen
    lcd.begin(numColm, numRows);
}

// Tømmer skjermen
void LiquidSkjerm::clear() {
    lcd.clear();
}

// Returnerer skjermens navn
String LiquidSkjerm::getName() {
    return name;
}