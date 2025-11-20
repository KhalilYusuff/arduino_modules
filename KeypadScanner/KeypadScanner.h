#pragma once
#include <Arduino.h>

// Definerer maks antall pinner for den manuelle scanningen
// Foreleserens kode bruker D2 til D8 (7 pinner)
#define MAX_PINS 7

class KeypadScanner {
private:
    // Pinner brukt for scanning: {2, 3, 4, 5, 6, 7, 8}
    const byte* keypadPins; 
    
    // Matrise som definerer mappingen: pins[i] vs pins[j] -> tast
    char mappingTable[MAX_PINS + 1][MAX_PINS + 1]; 
    
    unsigned long lastPressTime = 0;
    const unsigned long DEBOUNCE_DELAY_MS = 150; // Ikke-blokkerende debounce
    
    // Hjelpemetoder for scanning
    char mapKey(int pinA, int pinB);
    

public:
    char getScannedKey();
    // Konstruktør: Tar imot pin-arrayet og en 7x7 char-array for mapping
    // Merk: Denne mappingen er kompleks pga. den crude scannemetoden
    KeypadScanner(const byte* pins, char map[MAX_PINS + 1][MAX_PINS + 1]);

    // Hovedmetode: Returnerer tasten ELLER 0 (hvis ingen tast trykkes)
    char getKey(); 
};