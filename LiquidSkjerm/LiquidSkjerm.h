#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h> 

class LiquidSkjerm {
private:
    LiquidCrystal *lcd; 
    int numColm;
    int numRows;
    String name;

public:
    // Konstruktør: tar pinnene OG størrelsen
    LiquidSkjerm(int pinRS, int pinEN, int pinD4, int pinD5, int pinD6, int pinD7, 
                 int numRows, int numColm, String name);

    // Initialiserer skjermen (kaller lcd.begin)
    void begin(); 

    // Lag en enkel metode for å skrive tekst
    void write(const char* text, int col, int row);
    
    void clear();

    // Hjelpefunksjon
    String getName();
};