#include <Arduino.h>
#include <SPI.h> 
#include <MFRC522.h>


class RFID {
private: 
	MFRC522 *rfid1;
	String name;

	const byte** allowedUIDs;
	const byte* allowedLens;
	int allowedCount; 

public:
	RFID(int ssPin, int rstPin, String name,
			const byte** uids, const byte* lens, int count);

	~RFID();

	void begin();

	bool isNewCardPresent();

	void printUID();

	MFRC522::Uid* getUIDData();

	bool isAllowed();

	String getName();

};

