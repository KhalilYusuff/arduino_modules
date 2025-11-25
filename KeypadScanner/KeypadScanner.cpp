#include "KeypadScanner.h"

// Konstruktør – kopierer den dynamiske mappingstabellen
KeypadScanner::KeypadScanner(const byte* pins, char map[MAX_PINS + 1][MAX_PINS + 1])
    : keypadPins(pins) 
{
    // Kopier mappingstabellen
    for (int i = 0; i <= MAX_PINS; i++) {
        for (int j = 0; j <= MAX_PINS; j++) {
            mappingTable[i][j] = map[i][j];
        }
    }
}

// MapKey - Bruker den dynamisk oppgitte tabellen
char KeypadScanner::mapKey(int pinA, int pinB) {
    // Siden vi bruker minP og maxP i eksempelet, simulerer vi det her
    int minP = min(pinA, pinB);
    int maxP = max(pinA, pinB);
    
    // Returnerer den lagrede verdien fra den dynamiske tabellen
    // Vi bruker pin-nummeret som indeks (f.eks. pin 2 og 5)
    return mappingTable[minP][maxP]; 
}

// Kapsler inn foreleserens scannemetode
char KeypadScanner::getScannedKey() {
    // Foreleserens scanning: Set én pinne LOW, resten INPUT_PULLUP
    for (int i = 0; i < MAX_PINS; i++) {
        pinMode(keypadPins[i], OUTPUT);
        digitalWrite(keypadPins[i], LOW);

        for (int j = 0; j < MAX_PINS; j++) {
            if (i != j) {
                pinMode(keypadPins[j], INPUT_PULLUP);
                if (digitalRead(keypadPins[j]) == LOW) {
                    // Returner tasten uten debounce (Debounce håndteres i getKey())
                    return mapKey(keypadPins[i], keypadPins[j]);
                }
            }
        }
        // Tilbakestill pinnen til INPUT_PULLUP for neste iterasjon
        pinMode(keypadPins[i], INPUT_PULLUP);
    } 
    return 0; // Ingen tast trykket
}

// Hovedfunksjon: Ikke-blokkerende avlesing
char KeypadScanner::getKey() {
    char key = getScannedKey();

    if (key != 0) {
        // Debounce-logikk: Sjekk om nok tid har gått siden siste trykk
        if ((millis() - lastPressTime) > DEBOUNCE_DELAY_MS) {
            
            // Wait-for-release (forhindrer at tasten registreres flere ganger)
            // VIKTIG: Dette er en liten blokkering, men sikrer at kun ETT tegn leses
            while (getScannedKey() != 0) {
                // Vi venter til tasten slippes
            }
            
            lastPressTime = millis(); // Oppdater tiden for siste trykk
            return key;
        }
    }
    return 0; // Ingen gyldig tast
}