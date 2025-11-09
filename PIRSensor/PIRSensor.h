#pragma once
#include <Arduino.h>

class PIRDetector {
private:
    int detectionPin; // Digital pinne koblet til PIR OUT
    String name;
    
    //Variabel for å lagre tidspunktet for siste hendelse
    unsigned long lastMotion = 0; 

public:
    PIRDetector(String name, int pin);
    void begin();

    //Sjekker bevegelse og oppdaterer lastMotion.
    bool checkAndLogMotion(); 

    //Returnerer tid i millisekunder siden siste bevegelse.
    unsigned long timeSinceLastMotion(); 

    String getName();
};