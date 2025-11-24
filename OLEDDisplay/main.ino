#include "OLEDDisplay.h" 
#include <Wire.h> // Trengs for I2C

// Velg riktig adresse (0x3C eller 0x3D)
#define OLED_ADDRESS 0x3D 

// Deklarer OLED-objektet
OLEDDisplay screen("StatusDisplay", OLED_ADDRESS);

void setup() {
    Serial.begin(9600);
    Wire.begin(); // Veldig viktig å starte I2C-bussen først
    
    if (!screen.begin()) {
        Serial.println("OLED feilet. Sjekk koblinger.");
        while(true);
    }
    
    screen.setTextSize(2); // Større tekst for startmelding
    screen.startFrame();
    screen.println("SYSTEM STARTET");
    screen.endFrame();
    delay(2000);
}

void loop() {
    // 1. Rydd skjermen og sett startposisjon
    screen.startFrame(); 
    
    // 2. Skriv data
    screen.setTextSize(1);
    screen.println("Tid:");
    screen.setTextSize(2); // Større tid
    screen.println(String(millis() / 1000).c_str()); // Konverterer tid til sekunder
    
    // 3. Send bufferen til skjermen
    screen.endFrame(); 
    
    delay(100); 
}