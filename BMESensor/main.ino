#include "BME280Sensor.h"
#include <Serial.h> // Inkluderer Serial for utskrift

// Deklarer objektet (velg et navn)
BME280Sensor klimaSensor("Klimasjekk");

void setup() {
    Serial.begin(9600);
    
    // Starter sensoren og stopper om den feiler
    if (!klimaSensor.begin()) {
        while (1); // Stopp programmet ved feil
    }
}

void loop() {
    // Kaller metode for å få alle data
    BMEData currentData = klimaSensor.readData();

    Serial.print("Sensor: ");
    Serial.println(klimaSensor.getName());
    
    // Utskrift av målinger
    Serial.print("Temperatur: ");
    Serial.print(currentData.temperature);
    Serial.println(" *C");
    
    Serial.print("Fuktighet: ");
    Serial.print(currentData.humidity);
    Serial.println(" %");

    Serial.print("Trykk: ");
    Serial.print(currentData.pressure);
    Serial.println(" hPa");

    Serial.println("---");

    delay(2000); // Vent 2 sekunder
}