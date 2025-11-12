#include "ENS160Sensor.h"



// Konstruktør
ENS160Sensor::ENS160Sensor(String nName, int cs, int anInt) 
    : name(nName), csPin(cs), intPin(anInt) //Sender csPin til airSensor
{
    // Konstruktøren lagrer bare pinnene og navnet
}

/**
 * Starter I2C-kommunikasjon og ENS160-sensoren.
 */
bool ENS160Sensor::begin() {
    Serial.println("Starter ENS160 Luftkvalitetssensor (SPI)...");
    
    // 1. Initialiser SPI
    SPI.begin(); 
    
    //Sett CS-pinnen som OUTPUT og HIGH (Inaktiv tilstand)
    pinMode(csPin, OUTPUT); 
    digitalWrite(csPin, HIGH); // Sett CS høy for å deaktivere sensoren
    pinMode(intPin, INPUT); 

    
    // 2. Initialiser sensor.
    if (!airSensor.begin(csPin)) { 
        Serial.println("FEIL: Finner ikke ENS160 via SPI! Sjekk tilkobling/CS-pinne.");
        return false;
    }
    
    //
    airSensor.setOperatingMode(SFE_ENS160_RESET); 
    delay(100); // Venter etter Reset

    // 2. Sett Run-modus (0x02)
    airSensor.setOperatingMode(SFE_ENS160_STANDARD);

    Serial.println("ENS160 initialisert OK.");
    Serial.println("Merk: ENS160 trenger 3 minutter for stabil avlesning.");
    
    return true;
}

/**
 * Setter kompensasjonsverdier for å korrigere målingene.
 * Anbefales sterkt å bruke data fra BME280-modulen her.
 */
void ENS160Sensor::setCompensations(float tempC, float humidityRH) {
    // ENS160 bruker disse verdiene for å beregne nøyaktigere TVOC og eCO2
    airSensor.setTempCompensationCelsius(tempC);
    airSensor.setRHCompensationFloat(humidityRH);
}

/**
 * Leser alle verdier og returnerer en struktur.
 */
AirQualityData ENS160Sensor::readData() {
    AirQualityData data;
    
    data.aqi = 0;
    data.tvoc = 0;
    data.eco2 = 0;

    // Les de nyeste verdiene

    if (airSensor.checkDataStatus()){
        data.aqi = airSensor.getAQI();
        data.tvoc = airSensor.getTVOC();
        data.eco2 = airSensor.getECO2();
        return data;    
    }
    
    return data;
}

// Returnerer sensorens navn
String ENS160Sensor::getName() {
    return name;
}