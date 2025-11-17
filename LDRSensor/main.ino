#include "LDRSensor.h"

#define LDR_PIN A1      // Koble LDR til Analog Pin A1
#define LED_PIN 13      // Lys som skal slås på (f.eks. innebygd LED)
#define DARK_THRESHOLD 25 // 25% lys eller lavere regnes som mørkt

// Egendefinerte kalibreringspunkter
// VIKTIG: Sett disse basert på dine egne målinger i mørke/lys
#define MY_DARK_RAW 850
#define MY_BRIGHT_RAW 150

LDRSensor lysSensor("Ute-Lys", LDR_PIN);

void setup() {
    Serial.begin(9600);
    lysSensor.begin();
    
    // Sett de kalibrerte punktene for din LDR
    lysSensor.setCalibration(MY_DARK_RAW, MY_BRIGHT_RAW); 
    
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    
    // Filtrert verdi i % (0=mørkt, 100=lyst)
    int lightPercentage = lysSensor.getLightPercentage();
    
    Serial.print("Lysnivå: ");
    Serial.print(lightPercentage);
    Serial.print("% | ");
    
    // Bruker den dynamiske terskelmetoden
    if (lysSensor.isDark(DARK_THRESHOLD)) {
        Serial.println("STATUS: MØRKT (Slår PÅ lys)");
        digitalWrite(LED_PIN, HIGH);
    } else {
        Serial.println("STATUS: LYST nok (Slår AV lys)");
        digitalWrite(LED_PIN, LOW);
    }
    
    delay(500);
}