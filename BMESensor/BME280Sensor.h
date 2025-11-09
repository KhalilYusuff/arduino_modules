#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BME280.h> // Må inkluderes for BME280 funksjonalitet

// Struktur for å holde alle målinger samlet
struct BMEData {
    float temperature; // Temperatur i Celsius
    float humidity;    // Relativ fuktighet i prosent
    float pressure;    // Trykk i hPa (Hektopascal)
};

class BME280Sensor {
private:
    // Det private Adafruit BME280-objektet
    Adafruit_BME280 bme; 
    String name;
    
public:
    // Konstruktør: Tar et navn
    BME280Sensor(String name);

    // Initialiserer sensoren og sjekker status. Returnerer true ved suksess.
    bool begin();

    // Leser alle sensormålinger og returnerer BMEData-strukturen
    BMEData readData();
    
    // Hjelpemetode
    String getName();
};