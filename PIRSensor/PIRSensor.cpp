#include "PIRDetector.h"

// Konstruktør
PIRDetector::PIRDetector(String nName, int pin) 
    : name(nName), detectionPin(pin) 
{
    // Konstruktøren lagrer pinnen og navnet
}

/**
 * Initialiserer pinnen. 
 * Bruker standard INPUT. (Mange PIR-moduler har internt kretsløp som hindrer floating.)
 * Alternativt kan INPUT_PULLUP brukes hvis man opplever støy.
 */
void PIRDetector::begin() {
    pinMode(detectionPin, INPUT);
    
    // Hvis du opplever støy, kan du bruke:
    // pinMode(detectionPin, INPUT_PULLUP);
    
    Serial.print(name);
    Serial.println(" PIR-detektor initialisert.");
}
bool PIRDetector::checkAndLogMotion() {
    int pirState = digitalRead(detectionPin);
    
    if (pirState == HIGH) {
        //Oppdaterer lastMotion til NÅ
        this->lastMotion = millis(); 
        return true; 
    }
    return false;
}

/**
 * Kalkulerer hvor mange millisekunder det har gått siden siste bevegelse.
 * Viser hvor lenge en "tidtaker" har vært aktiv/inaktiv.
 */
unsigned long PIRDetector::timeSinceLastMotion() {
    // Dette håndterer "rollover" (at millis() går tilbake til 0) korrekt.
    // Nåtid (millis()) minus lagret tid (lastMotion).
    return millis() - this->lastMotion;
}

// Returnerer sensorens navn
String PIRDetector::getName() {
    return name;
}