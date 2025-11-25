#include "SmartAlarmSystem.h"
#include "PIRDetector.h" // Antatt modul
// ... inkluder andre sensorer her ...

SmartAlarmSystem alarmSystem;
PIRDetector pirSensor("Hovedinngang", 2);

void setup() {
    Serial.begin(9600);
    alarmSystem.begin();
    pirSensor.begin();
    // ... annen setup ...
}

void loop() {
    // ALLTID: Kjør systemets tilstandsmaskin
    alarmSystem.update(); 
    
    // --- Eksempel på Sensorlogikk ---
    
    // 1. Hvis Keypad leser 'A' (Aktiver)
    // if (keypad.getKey() == 'A') {
    //     alarmSystem.activate();
    // }

    // 2. Hvis Keypad leser 'D' (Deaktiver)
    // if (keypad.getKey() == 'D') {
    //     alarmSystem.deactivate();
    // }
    
    // 3. PIR Triggers (hvis PIR detekterer bevegelse)
    if (pirSensor.checkAndLogMotion()) {
        
        if (alarmSystem.getCurrentState() == ARMED) {
            
            // Simuler inngang via dør (gir tid til å taste kode)
            if (/* dør åpen */ true) { 
                alarmSystem.triggerAlarmDelayed(); 
            } else {
                // Simuler innbrudd via vindu (utløs umiddelbart)
                alarmSystem.triggerAlarmImmediate();
            }
        }
    }
    
    // --- Alarm Feedback Logikk ---
    
    if (alarmSystem.getCurrentState() == ALARM_ACTIVE) {
        // digitalWrite(ALARM_LED_PIN, HIGH);
        // buzzer.start();
    } else {
        // digitalWrite(ALARM_LED_PIN, LOW);
        // buzzer.stop();
    }
    
    delay(100); // Hold loop'en rask
}