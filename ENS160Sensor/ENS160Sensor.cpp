#include "ENS160Sensor.h"

// Standard I2C-adresse for ENS160 er 0x53

// Konstruktør
ENS160Sensor::ENS160Sensor(String nName) 
    : name(nName) 
{
    // airSensor-objektet initialiseres automatisk her
}

/**
 * Starter I2C-kommunikasjon og ENS160-sensoren.
 */
bool ENS160Sensor::begin() {
    Serial.println("Starter ENS160 Luftkvalitetssensor...");
    
    // Standard Wire.begin() for I2C
    Wire.begin(); 
    
    // airSensor.begin() returnerer true ved suksess
    if (!airSensor.begin()) {
        Serial.println("FEIL: Finner ikke ENS160 sensoren! Sjekk tilkobling/adresse.");
        return false;
    }
    
    Serial.println("ENS160 initialisert.");
    
    // Siden sensoren trenger ca. 3 minutter for stabil avlesning
    Serial.println("Merk: ENS160 trenger 3 minutter for stabil avlesning.");
    
    return true;
}

/**
 * Setter kompensasjonsverdier for å korrigere målingene.
 * Anbefales sterkt å bruke data fra BME280-modulen her.
 */
void ENS160Sensor::setCompensations(float tempC, float humidityRH) {
    // ENS160 bruker disse verdiene for å beregne nøyaktigere TVOC og eCO2
    airSensor.setTempCompensation(tempC);
    airSensor.setHumidityCompensation(humidityRH);
}

/**
 * Leser alle verdier og returnerer en struktur.
 */
AirQualityData ENS160Sensor::readData() {
    AirQualityData data;
    
    // Les de nyeste verdiene
    airSensor.measure(); 
    
    // Fyll strukturen med målingene
    data.aqi = airSensor.getAQI();
    data.tvoc = airSensor.getTVOC();
    data.eco2 = airSensor.geteCO2();
    
    return data;
}

// Returnerer sensorens navn
String ENS160Sensor::getName() {
    return name;
}