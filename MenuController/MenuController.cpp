#include "MenuController.h"
#include <string.h> // For strcpy, strcat, memset

// --- Private mapping funksjon ---
// Dette definerer hvilke taster som styrer menyen (kan endres i main.ino)
MenuKey MenuController::mapInputToMenuKey(char key) {
    switch (key) {
        case '2': return KEY_UP;
        case '8': return KEY_DOWN;
        case '#': return KEY_SELECT;
        case '*': return KEY_BACK;
        default: return KEY_NONE;
    }
}
// ------------------------------

// Konstruktør
MenuController::MenuController() : currentScreen(0), currentSelectionIndex(0), totalOptions(0) {
    // Tom konstruktør
}

void MenuController::begin() {
    currentSelectionIndex = 0; 
}

// Setter opp menyelementene
void MenuController::setupMenu(const MenuItem options[], int count) {
    totalOptions = min(count, MAX_OPTIONS);
    for (int i = 0; i < totalOptions; i++) {
        menuOptions[i] = options[i];
    }
}

// Hovedlogikk for navigasjon
void MenuController::processKey(char key) {
    MenuKey command = mapInputToMenuKey(key);

    if (totalOptions == 0) return; // Ikke naviger hvis menyen er tom

    switch (command) {
        case KEY_UP:
            // Ruller oppover (wrap rundt til bunn)
            currentSelectionIndex = (currentSelectionIndex - 1 + totalOptions) % totalOptions;
            break;
            
        case KEY_DOWN:
            // Ruller nedover (wrap rundt til topp)
            currentSelectionIndex = (currentSelectionIndex + 1) % totalOptions;
            break;

        case KEY_SELECT:
            // Logikk for valgt element sendes til Serial Monitor for debugging
            Serial.print(F("MENY VALGT: "));
            Serial.println(menuOptions[currentSelectionIndex].text);
            break;
            
        default:
            break;
    }
}

// Henter indeksen
int MenuController::getCurrentSelectionIndex() {
    return currentSelectionIndex;
}

// Henter teksten for det valgte elementet
const char* MenuController::getSelectedOptionText() {
    if (totalOptions > 0) {
        return menuOptions[currentSelectionIndex].text;
    }
    return "FEIL: Ingen meny satt";
}

// Fyller en 2D-array med teksten som skal vises på OLED
void MenuController::getScreenBuffer(char buffer[][20], int bufferSize) {
    if (totalOptions == 0) {
        // Bruker strcpy for å sikre null-terminering
        strcpy(buffer[0], "SETT OPP MENY");
        // Fyller resten med tomme strenger
        for (int i = 1; i < bufferSize; i++) {
            strcpy(buffer[i], " ");
        }
        return;
    }

    // Viser opptil 4 elementer (høyden på bufferSize) sentrert rundt valget
    int start = currentSelectionIndex; // Starter på valgt element
    if (start > 0) start--; // Prøver å vise elementet over valget

    
    for (int i = 0; i < bufferSize; i++) {
        int optionIndex = start + i;
        
        // Sjekker om indeksen er gyldig (og wrappes korrekt)
        if (optionIndex >= totalOptions) {
            strcpy(buffer[i], " "); // Tom linje
            continue;
        }

        if (optionIndex == currentSelectionIndex) {
            // Legg til markør ved valgt element
            strcpy(buffer[i], "> ");
            strcat(buffer[i], menuOptions[optionIndex].text);
        } else {
            // Uten markør
            strcpy(buffer[i], "  "); 
            strcat(buffer[i], menuOptions[optionIndex].text);
        }
    }
}