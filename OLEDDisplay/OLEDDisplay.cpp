#include "OLEDDisplay.h"

// Konstruktør: Initialiserer SSD1306-objektet i medlemslisten
// -1 for resetPin betyr at den ikke brukes.
OLEDDisplay::OLEDDisplay(String nName, int address, int resetPin)
    : name(nName), i2cAddress(address), 
      // Initialiserer Adafruit-objektet med bredde, høyde, Wire-buss, og resetPin
display(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, &Wire, resetPin, 100000UL, 16){
    // Konstruktøren lagrer bare data
}
/**
 * Initialiserer I2C-bussen og OLED-skjermen.
 * Returnerer true ved suksess.
 */
bool OLEDDisplay::begin() {
    Serial.println("Starter OLED Display...");
    
    // Antar Wire.begin() er kalt i setup()
    
    if (!display.begin(SSD1306_SWITCHCAPVCC, i2cAddress)) {
        Serial.println(F("FEIL: SSD1306 allocation failed."));
        return false;
    }

    // Standard oppsett for tekst
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.display(); // Vis den tomme skjermen

    Serial.println("OLED Display initialisert OK.");
    return true;
}

// Rydder skjermen og setter markøren til (0, 0)
void OLEDDisplay::startFrame() {
    display.clearDisplay();
    display.setCursor(0, 10);
}

// Sender bufferen til skjermen
void OLEDDisplay::endFrame() {
    display.display();
}

// Setter markøren
void OLEDDisplay::setCursor(int x, int y) {
    display.setCursor(x, y);
}

// Setter tekststørrelse
void OLEDDisplay::setTextSize(uint8_t size) {
    display.setTextSize(size);
}


// Hjelpemetode
String OLEDDisplay::getName() {
    return name;
}