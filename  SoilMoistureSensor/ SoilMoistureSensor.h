#pragma once
#include <Arduino.h>

class SoilMoistureSensor {
private:
    String name;
    int analogPin;
    
    // Konstanter for Signalbehandling
    static const int WINDOW_SIZE = 5; // Vindusstørrelse for Moving Average/Median Filter
    int readings[WINDOW_SIZE];
    int readIndex = 0;
    
    // Variabler for EMA (Exponential Moving Average)
    float EMA_ALPHA = 0.2; // Utjevningsfaktor (0.0 < alpha < 1.0)
    float EMA_value = 0.0;
    
    // Variabel for Adaptive Threshold
    float adaptiveThresholdValue = 50.0; // Startverdi for terskel
    float THRESHOLD_ADJUST_RATE = 0.05; // Hvor raskt terskelen skal endres

public:
    // Konstruktør
    SoilMoistureSensor(String name, int analogPin);

    // Initialisering av array
    void begin(); 
    
    // 1. Grunnleggende Lesing
    int readRawValue();

    // 2. Kalibrering
    int calibrateSensor(int minValue, int maxValue);

    // 3. Signalbehandling
    int movingAverage();
    int medianFilter();
    float exponentialMovingAverage();

    // 4. Avanserte Funksjoner
    // Setter og returnerer den dynamiske terskelen
    float adaptiveThreshold(); 
    
    // Varsler om signifikant endring
    int changeDetection(); 

    // Hjelpemetode
    String getName();
};