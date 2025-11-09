#pragma once
#include <Arduino.h>
#include <Wire.h> 
#include <SparkFun_ENS160.h> // Hovedbiblioteket for ENS160

// Struktur for å holde alle luftkvalitetsmålinger
struct AirQualityData {
    // Air Quality Index (1=Bra, 5=Svært Dårlig)
    uint8_t aqi;      
    // Total Volatile Organic Compounds (parts per billion)
    uint16_t tvoc;    
    // Equivalent CO2 (parts per million)
    uint16_t eco2;    
};

class ENS160Sensor {
private:
    // Det private ENS160-objektet
    ENS160 airSensor; 
    String name;
    
public:
    // Konstruktør: Tar kun et navn (I2C-adresse er som regel fast)
    ENS160Sensor(String name);

    // Initialiserer sensoren. Returnerer true ved suksess.
    bool begin();

    // Setter temperatur og fuktighet (viktig for nøyaktighet!)
    void setCompensations(float tempC, float humidityRH);

    // Leser alle sensormålinger og returnerer AirQualityData-strukturen
    AirQualityData readData();
    
    // Hjelpemetode
    String getName();
};