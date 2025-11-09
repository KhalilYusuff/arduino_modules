#include "PIRDetector.h"

#define PIR_OUT_PIN 2   // Definer pinnen PIR OUT er koblet til
#define LED_PIN 13      // Antatt LED-pinne for demonstrasjon
#define TIMEOUT_MS 10000 // 10 sekunder timeout

PIRDetector bevegelseSensor("Gang-Vakt", PIR_OUT_PIN);

void setup() {
    Serial.begin(9600);
    bevegelseSensor.begin();
    
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW); // Start med LED av
    
    Serial.println("Starter bevegelsesovervåking.");
}

void loop() {
    
    // 1. Sjekk for bevegelse og LOGG TIDSPUNKTET (ikke-blokkerende)
    if (bevegelseSensor.checkAndLogMotion()) {
        
        Serial.println("BEVEGELSE DETEKTERT! LED PÅ.");
        digitalWrite(LED_PIN, HIGH); // Slå PÅ lyset ved bevegelse
    }

    // 2. Sjekk Timer-logikk
    // Hvis tiden siden siste bevegelse er større enn timeout-tiden
    if (bevegelseSensor.timeSinceLastMotion() > TIMEOUT_MS) {
        
        // Sjekk om lyset faktisk er PÅ før vi slår det av, for å unngå gjentatt utskrift
        if (digitalRead(LED_PIN) == HIGH) {
             Serial.println("Bevegelse TIMET UT. LED AV.");
             digitalWrite(LED_PIN, LOW); // Slå AV lyset
        }
    }
    
    // Programmet går videre her uten å måtte vente 10 sekunder
    // Dette lar oss sjekke andre sensorer, oppdatere skjermer, etc.
}