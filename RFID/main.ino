#include "RFID.h" 

// --- DEKLARASJON AV WHITELIST (Eksempel) ---
// 1. Definerer selve UID-arrayet. Bruker den lengste UID-en (her 7) for dimensjonen
const byte ALLOWED_UIDS[][7] = {
    // UID 1: 4 bytes (pad med 0x00)
    {0xA1, 0xB2, 0xC3, 0xD4, 0x00, 0x00, 0x00}, 
    // UID 2: 7 bytes
    {0x04, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC},
    {0x7A, 0x2C, 0x0F, 0xB0, 0x00, 0x00, 0x00} 
};

// 2. Definerer lengden for hver tilsvarende UID
const byte ALLOWED_LENS[] = {4, 7, 4};

// 3. Definerer antall elementer
const int ALLOWED_COUNT = 3; 

// Konverterer 2D-arrayet til en peker-array for å sende det til klassen
const byte* UID_POINTERS[ALLOWED_COUNT] = {
    ALLOWED_UIDS[0],
    ALLOWED_UIDS[1], 
    ALLOWED_UIDS[2],
};
// ------------------------------------------

#define SS_PIN 10
#define RST_PIN 9

// Oppretterer objektet og sender inn de dynamiske parameterne
RFID rfidReader(SS_PIN, RST_PIN, "Inngangsleser", 
                UID_POINTERS, ALLOWED_LENS, ALLOWED_COUNT);


void setup() {
    Serial.begin(9600);
    rfidReader.begin(); 
}

void loop() {
    // henter uid, om det skulle brukes i LCD eller noe lignende
    MFRC522::Uid* uidData = rfidReader.getUIDData();

    // Konverterer UID til en String/Char Array for utskrift på LCD
        String uidStr = "";
        for (byte i = 0; i < uidData->size; i++) {
            // Legger til byte i Stringen (f.eks. A1)
            char hexByte[3];
            sprintf(hexByte, "%02X", uidData->uidByte[i]); // Formater byte til 2 HEX-tegn
            uidStr += hexByte;
            uidStr += " "; // Mellomrom mellom bytes
        }

    if (rfidReader.isNewCardPresent()) {
        rfidReader.printUID();

        // Kaller den dynamiske sjekken
        if (rfidReader.isAllowed()) {
            Serial.println(" -> TILGANG TILLATT!");
        } else {
            Serial.println(" -> TILGANG NEKTET.");
        }
        
    }
}