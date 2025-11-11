#include "PIRSensor.h"

// Konstruktør
PIRSensor::PIRSensor(String nName, int pin) 
    : name(nName), detectionPin(pin) 
{
    // Konstruktøren lagrer pinnen og navnet
}

/**
 * Initialiserer pinnen. 
 * Bruker standard INPUT. (Mange PIR-moduler har internt kretsløp som hindrer floating.)
 * Alternativt kan INPUT_PULLUP brukes hvis man opplever støy.
 */
void PIRSensor::begin() {
    pinMode(detectionPin, INPUT);
    
    // Hvis du opplever støy, kan du bruke:
    // pinMode(detectionPin, INPUT_PULLUP);
    
    Serial.print(name);
    Serial.println(" PIR-detektor initialisert.");
}
bool PIRSensor::checkAndLogMotion() {
    int pirState = digitalRead(detectionPin);
    
    if (pirState == HIGH) {
        //Oppdaterer lastMotion til NÅ
        this->lastMotion = millis(); 
        return true; 
    }
    return false;
}
bool PIRSensor::checkMotion(){
    int state = digitalRead(detectionPin);

    if (state == HIGH){
        return true;
    }
    return false;
}

/**
 * Kalkulerer hvor mange millisekunder det har gått siden siste bevegelse.
 * Viser hvor lenge en "tidtaker" har vært aktiv/inaktiv.
 */
unsigned long PIRSensor::timeSinceLastMotion() {
    // Dette håndterer "rollover" (at millis() går tilbake til 0) korrekt.
    // Nåtid (millis()) minus lagret tid (lastMotion).
    return millis() - this->lastMotion;
}

// Returnerer sensorens navn
String PIRSensor::getName() {
    return name;
}