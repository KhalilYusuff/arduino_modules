#include "SmartAlarmSystem.h"

// Konstruktør
SmartAlarmSystem::SmartAlarmSystem() {
    // Tom konstruktør – initialisering skjer i begin()
}

// Internt verktøy: Bytter tilstand og setter tidsstempel
void SmartAlarmSystem::transitionTo(AlarmState newState) {
    currentState = newState;
    stateStartTime = millis();
    
    Serial.print("ALARM STATUS: ");
    
    // Viser den nye tilstanden for debugging
    switch (newState) {
        case DISARMED: Serial.println("DEAKTIVERT."); break;
        case ARMING_DELAY: Serial.println("AKTIVERER (30 sek nedtelling)..."); break;
        case ARMED: Serial.println("AKTIVERT og SIKRET."); break;
        case TRIGGERED_DELAY: Serial.println("INNBRUDD VARSLET (10 sek nedtelling)..."); break;
        case ALARM_ACTIVE: Serial.println("!!! ALARM UTLØST !!!"); break;
    }
}

// Starter systemet
void SmartAlarmSystem::begin() {
    transitionTo(DISARMED);
}

// Setter alarmen i utgående forsinkelse
void SmartAlarmSystem::activate() {
    if (currentState == DISARMED) {
        transitionTo(ARMING_DELAY);
    }
}

// Deaktiverer systemet
void SmartAlarmSystem::deactivate() {
    if (currentState != DISARMED) {
        transitionTo(DISARMED);
    }
}

// Utløser alarmen umiddelbart (f.eks. PIR/glassbrudd)
void SmartAlarmSystem::triggerAlarmImmediate() {
    if (currentState == ARMED) {
        transitionTo(ALARM_ACTIVE);
    }
}

// Setter inngående forsinkelse (f.eks. dør åpnes)
void SmartAlarmSystem::triggerAlarmDelayed() {
    if (currentState == ARMED) {
        transitionTo(TRIGGERED_DELAY);
    }
}

// Returnerer tiden i gjeldende tilstand
unsigned long SmartAlarmSystem::timeInCurrentState() {
    return millis() - stateStartTime;
}

// Returnerer gjeldende tilstand
AlarmState SmartAlarmSystem::getCurrentState() {
    return currentState;
}

/**
 * Hovedmetode: Håndterer tidtakere og automatiske tilstandsskifter.
 * MÅ kalles hyppig i loop().
 */
void SmartAlarmSystem::update() {
    unsigned long timeElapsed = timeInCurrentState();

    switch (currentState) {
        case ARMING_DELAY:
            // Sjekk: Har utgående forsinkelse utløpt?
            if (timeElapsed >= ARMING_DELAY_MS) {
                transitionTo(ARMED);
            }
            break;

        case TRIGGERED_DELAY:
            // Sjekk: Har inngående forsinkelse utløpt UTEN deaktivering?
            if (timeElapsed >= TRIGGERED_DELAY_MS) {
                transitionTo(ALARM_ACTIVE);
            }
            break;

        case ALARM_ACTIVE:
            // Alarmen er aktiv. Krever manuell deaktivering.
            // (Ingen automatisk tilstandsskifte her, venter på deactivate())
            break;

        // I alle andre tilfeller, gjør ingenting automatisk.
        default:
            break;
    }
}