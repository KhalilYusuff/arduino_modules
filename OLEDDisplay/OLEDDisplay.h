#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// ... (eksisterende includes) ...

#define DEFAULT_SCREEN_WIDTH 128
#define DEFAULT_SCREEN_HEIGHT 64

class OLEDDisplay {
private:
    // ... (private felt) ...
    Adafruit_SSD1306 display;
    String name;
    int i2cAddress;
    
public:
    // ... (konstruktør og begin()) ...
    OLEDDisplay(String name, int address, int resetPin = -1);

    bool begin();

     // Rydder skjermen og setter markøren til (0, 0)
    void startFrame(); 

    // Viser bufferen på skjermen (display.display())
    void endFrame(); 
    
    // Setter markøren
    void setCursor(int x, int y);

    // Konfigurerer tekststørrelse
    void setTextSize(uint8_t size);

    template <typename T>
    void print(T value) {
        display.print(value);
    }
    
    template <typename T>
    void println(T value) {
        display.println(value);
    }

    String getName();
};