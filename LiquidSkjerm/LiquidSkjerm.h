#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h> 

class LiquidSkjerm {
private:
    LiquidCrystal lcd; 
    int numColm;
    int numRows;
    String name;

public:
    // Konstruktør: tar pinnene OG størrelsen
    LiquidSkjerm(int pinRS, int pinEN, int pinD4, int pinD5, int pinD6, int pinD7, 
                 int numRows, int numColm, String name);

    // Initialiserer skjermen (kaller lcd.begin)
    void begin(); 

    // Skriver tekst til en spesifikk kolonne og rad
    template <typename T>
    void write(T value, int col, int row){
        lcd.setCursor(col, row);
        lcd.print(value);
    }
    
    void clear();

    // Hjelpefunksjon
    String getName();
};