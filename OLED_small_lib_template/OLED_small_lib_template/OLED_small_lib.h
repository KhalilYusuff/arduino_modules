//
// Created by Poteten on 23.11.2025.
//

#ifndef ARDUINO_SENSOR_LIBRARY_OLED_SMALL_LIB_H
#define ARDUINO_SENSOR_LIBRARY_OLED_SMALL_LIB_H

#include <SSD1306AsciiAvrI2c.h>

#define I2C_ADDRESS 0x3C
#define RST_PIN (-1)

class OLED_small_lib : public SSD1306AsciiAvrI2c {
public:
    OLED_small_lib();
    void initializeDisplay();
    void printLine(signed int line, const String& text, signed int textSize);

private:
    int lineHeight{};
    int y{};
};


#endif //ARDUINO_SENSOR_LIBRARY_OLED_SMALL_LIB_H