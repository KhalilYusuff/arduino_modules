#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h> // Må inkluderes

class LiquidSkjerm {
private:
    // **VIKTIG:** Deklarer LiquidCrystal-objektet som et privat medlem
    LiquidCrystal *lcd; // Bruk en peker for å initialisere det i konstruktøren (anbefalt)
    
    // Disse er fortsatt fine å lagre, men er kanskje ikke nødvendige
    // int pin12, pin11, pin5, pin4, pin3, pin2; 
    int numColm;
    int numRows;
    String name;

public:
    // Konstruktør: tar pinnene OG størrelsen
    LiquidSkjerm(int pinRS, int pinEN, int pinD4, int pinD5, int pinD6, int pinD7, 
                 int numRows, int numColm, String name);

    // Initialiserer skjermen (kaller lcd.begin)
    // Fjern parametere her, de er lagret i klassen
    void begin(); 

    // Lag en enkel metode for å skrive tekst
    void write(const char* text, int col, int row);
    
    // Lag en metode for å tømme skjermen
    void clear();

    // Hjelpefunksjon
    String getName();
};