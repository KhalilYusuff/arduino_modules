#include <Arduino.h>

class Keypad2{
private: 
	const byte keypadPins[7];
	String name 

public:
	Keypad2(byte keypadPins, String name);

	void begin();

	char getPressedKey();

	char mapKey(int a, int b);
}

