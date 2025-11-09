#include "ENS160Sensor.h"
#include "BME280Sensor.h" //Brukes for temperatur/fuktighet(https://github.com/KhalilYusuff/arduino_modules/tree/main/BMESensor)

// Deklarer objekter
BME280Sensor klimaSensor("Klimasjekk");
ENS160Sensor luftSensor("Luftkvalitet");

void setup() {
    Serial.begin(9600);
    
    if (!klimaSensor.begin() || !luftSensor.begin()) {
        while(1); // Stopp ved feil
    }
    
    Serial.println("System klart.");
}

void loop() {
    // 1. Les data fra BME280 (trengs for kompensasjon)
    BMEData klimaData = klimaSensor.readData();

    // 2. Sett kompensasjonsverdier i ENS160
    luftSensor.setCompensations(klimaData.temperature, klimaData.humidity);
    
    // 3. Les data fra ENS160
    AirQualityData luftData = luftSensor.readData();

    // --- Utskrift av Luftkvalitet ---
    Serial.println("================================");
    Serial.print("Sensor: ");
    Serial.println(luftSensor.getName());
    
    Serial.print("AQI: ");
    Serial.print(luftData.aqi);
    Serial.println(" (1=Bra, 5=S. Darlig)");
    
    Serial.print("eCO2: ");
    Serial.print(luftData.eco2);
    Serial.println(" ppm");
    
    Serial.print("TVOC: ");
    Serial.print(luftData.tvoc);
    Serial.println(" ppb");
    
    Serial.println("================================");

    delay(5000); 
}