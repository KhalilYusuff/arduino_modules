#pragma once
#include <Arduino.h>

class PIRSensor {
private:
    int detectionPin; // Digital pinne koblet til PIR OUT
    String name;
    
    //Variabel for å lagre tidspunktet for siste hendelse
    unsigned long lastMotion = 0; 

public:
    PIRSensor(String name, int pin);
    void begin();

    //Sjekker bevegelse og oppdaterer lastMotion.
    bool checkAndLogMotion(); 

    bool checkMotion();

    //Returnerer tid i millisekunder siden siste bevegelse.
    unsigned long timeSinceLastMotion(); 

    String getName();
};