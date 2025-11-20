#include "KeypadScanner.h"

// Pin Layout: D2 til D8
const byte KEYPAD_PINS[MAX_PINS] = {2, 3, 4, 5, 6, 7, 8};

// Definisjon av den 7x7 dynamiske mappingstabellen (Indekser er PINTALL)
// Vi bruker en 8x8 tabell for å unngå å tenke på indeks 0 og 1.
// mappingTable[MIN_PIN][MAX_PIN] = 'Tast'
char EXAM_LAYOUT[MAX_PINS + 1][MAX_PINS + 1] = { 0 }; 

// Deklarer Keypad-objektet
KeypadScanner keypad(KEYPAD_PINS, EXAM_LAYOUT);

void setup() {
    Serial.begin(9600);
    
    // --- Dynamisk Mapping MÅ Gjøres Her ---
    // Dette er den tidligere hardkodede mapKey logikken, men nå dynamisk:
    // EXAM_LAYOUT[minP][maxP] = 'Tast'
    EXAM_LAYOUT[3][4] = '1'; 
    EXAM_LAYOUT[2][3] = '2'; 
    EXAM_LAYOUT[3][6] = '3'; 
    EXAM_LAYOUT[4][8] = '4'; 
    EXAM_LAYOUT[2][8] = '5'; 
    EXAM_LAYOUT[6][8] = '6'; 
    EXAM_LAYOUT[4][7] = '7'; 
    EXAM_LAYOUT[2][7] = '8'; 
    EXAM_LAYOUT[6][7] = '9'; 
    EXAM_LAYOUT[2][5] = '0'; 
    EXAM_LAYOUT[4][5] = '*'; 
    EXAM_LAYOUT[5][6] = '#'; 
    // ----------------------------------------
    
    Serial.println("Keypad Scanner Ready.");
}

void loop() {
    // Sjekk for tastetrykk (Ikke-blokkerende)
    char key = keypad.getKey(); 
    
    if (key != 0) {
        Serial.print("Key pressed: ");
        Serial.println(key);
    }
    
    // Annen logikk her (BME, PIR, LDR, etc.)
}