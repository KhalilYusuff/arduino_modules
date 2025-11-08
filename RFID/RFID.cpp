¨#Inclid "RFID.h"

RFID::RFID(int ssPin, int rstPin, String nName,
			const byte** uids, const byte* lens, int count)
	: name(nName), allowedUIDs(uids), allowedLens(lens), allowedCount(count)
{
	rfid1 = new MFRC522(ssPin, rstPin);
}

RFID::~RFID(){
	delete rfid1;	
}

void RFID::begin(){
	SPI.begin();
	rfid1->PCD_Init();
	Serial.println(F("RFID-leser initialisert."));
}

void RFID::isNewCardPresent(){
	return (rifd1->PICC_IsNewCardPresent() && rfid1->PICC_ReadCardSerial());
}

void RFID::printUID(){
	Serial.print(name);
	Serial.print(" leste: ");

	for (byte i = 0; i < rfid->uid.size; i++){
		if (rfid1->uid.Byte[i] < 0x10){
			Serial.print(0);
		}
		Serial.print(rfid1->uid.uiByte[i], HEX);
		Serial.print(" ");
	}
	Serial.print();
	rfid1->PICC_HaltA();
}

MFRC522::Uid* RFID::getUIDData(){
	if (rfid1->PICC_IsNewCardPresent() && rfid1->PICC_>ReadCardSerial()){
		return &rfid1->uid:
	}
	return nullptr;
}


bool RIFD::isAllowed(){
	const byte *uid = rfid1->uid.uiByte; 
	byte len = rfid1->uid.size;

	for (int i = 0, i < this->allowedCount; i++){
		
		if (len != this.allowedLens[i]){
			continue;
		}
		bool match = true; 

		for (byte j = 0; j < len; j++){
			if (uid[j] != this->allowedCount[i][j]){
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