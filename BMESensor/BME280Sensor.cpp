#include "BME280Sensor.h"

// Konstruktør: Tar imot navn og initialiserer private felt
BME280Sensor::BME280Sensor(String nName) 
    : name(nName) 
{
    // Objektet bme initialiseres automatisk her.
}

// Starter sensoren og I2C-kommunikasjon
bool BME280Sensor::begin() {
    Serial.println("Starter BME280 Sensor...");
    
    // Wire.begin() er nødvendig for I2C og kalles vanligvis i setup(), 
    // men vi kaller den her for å sikre at modulen er selvstendig
    Wire.begin(); 
    
    // Standard I2C-adresse for BME280 er 0x76 (eller 0x77). 
    // Vi bruker standardadressen her.
    unsigned status = bme.begin(); 

    if (!status) {
        Serial.println("FEIL: Finner ikke BME280! Sjekk tilkobling/adresse.");
        return false;
    }
    
    Serial.println("BME280 initialisert OK.");
    return true;
}

// Leser alle verdier og returnerer en struktur
BMEData BME280Sensor::readData() {
    BMEData data;
    
    // Adafruit BME280-biblioteket returnerer:
    // - Temperatur i Celsius
    // - Fuktighet i %
    // - Trykk i Pascal (Pa), så vi deler med 100 for hPa
    
    data.temperature = bme.readTemperature();
    data.humidity = bme.readHumidity();
    data.pressure = bme.readPressure() / 100.0F; // Konverterer Pa til hPa

    return data;
}

// Returnerer sensorens navn
String BME280Sensor::getName() {
    return name;
}