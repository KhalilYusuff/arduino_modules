#include "RFID.h"


RFID::RFID(int ssPin, int rstPin, String nName, 
           const byte** uids, const byte* lens, int count)
    : name(nName), allowedUIDs(uids), allowedLens(lens), allowedCount(count) 
{
    rfid1 = new MFRC522(ssPin, rstPin);
}

bool RFID::isNewCardPresent(){
	return (rfid1->PICC_IsNewCardPresent() && rfid1->PICC_ReadCardSerial());
}

void RFID::begin() {
    SPI.begin();       // Starter SPI kommunikasjon
    rfid1->PCD_Init(); // Starter MFRC522-modulen
    Serial.println(F("RFID-leser initialisert."));
}

RFID::~RFID() {
    delete rfid1;
}

void RFID::printUID(){
	Serial.print(name);
	Serial.print(" leste: ");

	for (byte i = 0; i < rfid1->uid.size; i++){ 
		if (rfid1->uid.uidByte[i] < 0x10){ 
			Serial.print("0"); 
		}
		Serial.print(rfid1->uid.uidByte[i], HEX); 
		Serial.print(" ");
	}
	Serial.println(); 
	rfid1->PICC_HaltA();
}

MFRC522::Uid* RFID::getUIDData(){
	if (rfid1->PICC_IsNewCardPresent() && rfid1->PICC_ReadCardSerial()){
		return &rfid1->uid;
	}
	return nullptr;
}


bool RFID::isAllowed(){
	const byte *uid = rfid1->uid.uidByte;
	byte len = rfid1->uid.size;

	for (int i = 0; i < this->allowedCount; i++){ 
		
		if (len != this->allowedLens[i]){
			continue;
		}
		bool match = true;

		for (byte j = 0; j < len; j++){
			if (uid[j] != this->allowedUIDs[i][j]){ 
			match = false;
			break;
			}
		}
		if (match){
			return true;
		}
	}
	return false;
}