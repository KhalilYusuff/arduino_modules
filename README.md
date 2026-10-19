# Arduino Modules

Collection of reusable Arduino sensor and device modules, plus small integration demos.

## Repository structure

Each module lives in its own folder and includes a `main.ino` example sketch.

- `BaseSensor` – shared base class for sensor modules
- `BMESensor` – BME280 temperature, humidity, and pressure
- `ENS160Sensor` – ENS160 air quality (AQI/TVOC/eCO2)
- `LDRSensor` – light sensor with filtering and calibration
- `PIRSensor` – motion detection
- `RFID` – MFRC522 RFID reader support
- `LiquidSkjerm` – 16x2 LCD wrapper
- `OLEDDisplay` / `OLED_small_lib_template` – OLED display utilities
- `Keypad1` / `KeypadScanner` – keypad input modules
- `MenuController` – keypad-driven menu state handling
- `SmartAlarmSystem` – alarm state machine example
- `SoilMoistureSensor` – soil moisture readings and filtering

## Requirements

- Arduino IDE (or compatible build environment)
- Board support package for your target board
- Libraries used by the modules (as needed):
  - `SparkFunBME280`
  - `SparkFun_ENS160`
  - `Adafruit_GFX`
  - `Adafruit_SSD1306`
  - `Keypad`
  - `MFRC522`
  - `LiquidCrystal`
  - `SSD1306Ascii`

## Usage

1. Open the folder for the module you want to use.
2. Open that folder’s `main.ino`.
3. Install any required libraries listed above.
4. Adjust pin assignments for your hardware.
5. Upload and test on your board.

## Notes

- Most comments and naming are in Norwegian.
- Module APIs are declared in each module’s header file (`*.h`).
