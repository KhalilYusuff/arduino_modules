#pragma once
#include <Arduino.h>

// --- GLOBALT TILGJENGELIGE DEFINISJONER ---

// Definerer de logiske tastene som brukes for navigasjon i modulen
enum MenuKey {
    KEY_NONE,
    KEY_UP,
    KEY_DOWN,
    KEY_SELECT,
    KEY_BACK
};

// NÅ TILGJENGELIG GLOBAL (kan brukes i main.ino for å definere menyelementer)
struct MenuItem { 
    const char* text;
    // Du kan legge til en action ID (int) her senere hvis nødvendig
};

// ------------------------------------------

class MenuController {
private:
    static const int MAX_OPTIONS = 5;
    MenuItem menuOptions[MAX_OPTIONS]; // Bruker den globale strukturen
    
    int currentScreen; 
    int currentSelectionIndex;
    int totalOptions; 
    
    // Konverterer de faktiske tastene ('2', '8', '#') til logiske menytaster
    MenuKey mapInputToMenuKey(char key);

public:
    // Konstruktør
    MenuController();

    // Starter menyen (setter starttilstand)
    void begin(); 
    
    // Setter opp menyelementene (kalt fra setup i main.ino)
    void setupMenu(const MenuItem options[], int count);

    // Hovedmetode: Mottar tastetrykk og oppdaterer tilstanden
    void processKey(char key); 

    // --- Metoder for OLED Display (Henter data) ---

    // Henter teksten for det valgte elementet
    const char* getSelectedOptionText(); 

    // Fyller en 2D-buffer med teksten som skal vises på OLED (inkl. markering)
    void getScreenBuffer(char buffer[][20], int bufferSize);

    // Returnerer den valgte indeksen (for logikk i main.ino)
    int getCurrentSelectionIndex();
};