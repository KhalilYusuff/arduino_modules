#include "LiquidSkjerm.h"

// Konstruktør
LiquidSkjerm::LiquidSkjerm(int pinRS, int pinEN, int pinD4, int pinD5, int pinD6, int pinD7, 
                           int nRows, int nColm, String nName)
    : numColm(nColm), numRows(nRows), name(nName) 
{
    // 1. Alloker minne for LiquidCrystal-objektet (pekeren 'lcd')
    // Her initialiseres LiquidCrystal-bibliotekets objekt med pinnene
    lcd = new LiquidCrystal(pinRS, pinEN, pinD4, pinD5, pinD6, pinD7);
    
}

// Initialiserer skjermen (kaller LiquidCrystal::begin)
void LiquidSkjerm::begin() {
    // 2. Kall LiquidCrystal-objektets begin() metode med størrelsen
    lcd->begin(numColm, numRows);
}

// Skriver tekst til en spesifikk kolonne og rad
void LiquidSkjerm::write(const char* text, int col, int row) {
    lcd->setCursor(col, row);
    lcd->print(text);
}

// Tømmer skjermen
void LiquidSkjerm::clear() {
    lcd->clear();
}

// Returnerer skjermens navn
String LiquidSkjerm::getName() {
    return name;
}