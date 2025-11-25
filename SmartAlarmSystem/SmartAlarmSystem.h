#pragma once
#include <Arduino.h>

// Definerer alle mulige tilstander systemet kan være i
enum AlarmState {
    DISARMED,         // Systemet er Deaktivert (Normal tilstand)
    ARMING_DELAY,     // Utgående Forsinkelse (Gir tid til å forlate huset)
    ARMED,            // Systemet er Aktivert (Sikret)
    TRIGGERED_DELAY,  // Inngående Forsinkelse (Gir tid til å taste kode)
    ALARM_ACTIVE,     // Alarmen er utløst!
};

class SmartAlarmSystem {
private:
    AlarmState currentState;
    unsigned long stateStartTime; // Tidsstempel for når nåværende tilstand startet
    
    // Standard tidsinnstillinger (kan justeres i konstruktør eller setter-metoder)
    const unsigned long ARMING_DELAY_MS = 30000;   // 30 sek utgående
    const unsigned long TRIGGERED_DELAY_MS = 10000; // 10 sek inngående
    
    // Intern metode for å bytte tilstand og starte tidtaker
    void transitionTo(AlarmState newState); 

public:
    // Konstruktør
    SmartAlarmSystem();

    // Starter systemet i DISARMED modus
    void begin(); 

    // --- Systemkontroll (Utløses av Keypad/RFID) ---

    // Setter systemet i ARMING_DELAY
    void activate(); 

    // Deaktiverer alarmen fra enhver tilstand
    void deactivate(); 
    
    // Utløser alarmen umiddelbart (F.eks. ved brudd gjennom vindu/PIR)
    void triggerAlarmImmediate();
    
    // Setter systemet i TRIGGERED_DELAY (F.eks. ved åpning av dør)
    void triggerAlarmDelayed(); 
    
    // --- Status og Tidssjekk (Brukes i Loop) ---

    // Returnerer gjeldende tilstand (enum)
    AlarmState getCurrentState(); 

    // Returnerer hvor lenge systemet har vært i gjeldende tilstand (millis)
    unsigned long timeInCurrentState();
    
    // Hovedmetode: MÅ kalles i loop. Håndterer tidtakere og tilstandsskifter.
    void update(); 

    // Hjelpemetode for Keypad/Nødknapp
    void setEmergencyOverride(); 
};