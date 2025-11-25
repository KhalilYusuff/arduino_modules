#include "LDRSensor.h"

// Konstruktør
LDRSensor::LDRSensor(String nName, int pin) 
    : name(nName), analogPin(pin) 
{
    // Initialiserer her
}

// Initialiserer filter-arrayen og pinnen
void LDRSensor::begin() {
    // LDR er en analog sensor, men det skader ikke å sette pinne-modus
    pinMode(analogPin, INPUT); 
    
    // Initialiserer arrayen for Moving Average
    for (int i = 0; i < WINDOW_SIZE; i++) {
        readings[i] = 0;
    }
    Serial.print(name);
    Serial.println(" LDR Sensor initialisert.");
}

// Setter kalibreringspunkter (kan kalles i setup eller dynamisk)
void LDRSensor::setCalibration(int dark, int bright) {
    this->darkValue = dark;
    this->brightValue = bright;
}

// Leser råverdien
int LDRSensor::readRawValue() {
    return analogRead(this->analogPin);
}

// Leser filtrert verdi ved hjelp av Moving Average
int LDRSensor::readFilteredValue() {
    int rawValue = readRawValue();
    
    // Legg til ny lesing i det rullerende vinduet
    readings[readIndex] = rawValue;
    readIndex = (readIndex + 1) % WINDOW_SIZE; 

    long total = 0;
    for (int i = 0; i < WINDOW_SIZE; i++) {
        total += readings[i];
    }
    
    return total / WINDOW_SIZE;
}

/**
 * Returnerer lysnivået som prosent. 
 * Bruker omvendt mapping (Høyt råtall = Mørkt/Lav prosent).
 */
int LDRSensor::getLightPercentage() {
    // Bruk den filtrerte verdien for stabil %-visning
    int filteredValue = readFilteredValue();
    
    // [darkValue (Lav), brightValue (Høy)] til [0% (mørkt), 100% (lyst)]
    int lightPercent = map(filteredValue, darkValue, brightValue, 0, 100);
    // Sikrer at verdien holder seg innenfor [0, 100]
    return constrain(lightPercent, 0, 100);
}

/**
 * Sjekker om lysnivået er under en gitt terskel.
 * F.eks. isDark(30) -> returnerer true hvis lyset er under 30%.
 */
bool LDRSensor::isDark(int thresholdPercent) {
    int currentPercent = getLightPercentage();
    
    // Lav prosent = Mørkt.
    // Hvis currentPercent (f.eks. 20%) er lavere enn threshold (f.eks. 30%)
    return currentPercent < thresholdPercent;
}

String LDRSensor::getName() {
    return name;
}