#pragma once
#include <Arduino.h>

class LDRSensor {
private:
    int analogPin;
    String name;
    
    // Kalibrering: Disse bør settes i begin() eller via en metode
    int darkValue = 800;  // Råverdi for "helt mørkt"
    int brightValue = 100; // Råverdi for "helt lyst"
    
    // Konstanter for Moving Average (filtrering)
    static const int WINDOW_SIZE = 10; 
    int readings[WINDOW_SIZE];
    int readIndex = 0;
    
public:
    // Konstruktør
    LDRSensor(String name, int pin);

    // Initialiserer sensor/filter
    void begin();
    
    // Setter de dynamiske kalibreringspunktene
    void setCalibration(int dark, int bright);

    // Leser råverdien direkte
    int readRawValue();

    // Leser filtrert verdi ved hjelp av Moving Average
    int readFilteredValue();

    // Returnerer lysnivået som prosent (0% = mørkt, 100% = lyst)
    int getLightPercentage();

    // Returnerer boolsk status basert på en terskel (f.eks. for å slå på lys)
    bool isDark(int thresholdPercent);
    
    String getName();
};