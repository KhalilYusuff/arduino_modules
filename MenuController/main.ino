// main.ino (EKSEMPEL)
#include "KeypadScanner.h" 
#include "MenuController.h" 
// ... inkluder OLEDDisplay.h ...

// Definerer menyelementene
const MenuItem mainMenuOptions[] = {
    {"Aktiver Alarm", },
    {"Deaktiver Alarm", },
    {"Vis Stats", },
    {"Sett Kode", },
    {"Gaa Tilbake", }
};
const int NUM_MENU_OPTIONS = 5;

// Deklarer objektet
MenuController menu;
// ... (Globale variabler) ...

void setup() {
    // ... (annen setup) ...
    
    menu.begin();
    menu.setupMenu(mainMenuOptions, NUM_MENU_OPTIONS);
}

void loop() {
    // Antar at KeypadScanner er deklarert globalt
    char key = keypadScanner.getKey(); 
    
    if (key != 0) {
        // 1. Send tastetrykket til menymodulen
        menu.processKey(key); 
    }
    
    // 2. Hent data og vis på OLED
    displayMenuScreen(); // Må implementeres
    
    // ... (Resten av loop-logikken) ...
}