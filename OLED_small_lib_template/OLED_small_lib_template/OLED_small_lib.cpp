//
// Created by Poteten on 23.11.2025.
//

#include "OLED_small_lib.h"

OLED_small_lib::OLED_small_lib() : SSD1306AsciiAvrI2c() { }

void OLED_small_lib::initializeDisplay() {
    begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
    setFont(System5x7);
}
