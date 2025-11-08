#include <Arduino.h>
#include "SoilMoistureSensor.h" 

// --- Definisjoner ---
#define MOISTURE_PIN A0 // Analog pinne sensoren er koblet til

// Kalibreringsverdier for sensoren:
// Laveste råverdi (sensor tørr, typisk i luft)
const int DRY_CALIBRATION_VALUE = 800; 
// Høyeste råverdi (sensor våt, typisk i vann)
const int WET_CALIBRATION_VALUE = 400; 
// Merk: Disse verdiene kan variere sterkt og må tilpasses din sensor og jord.

// --- Objekt Deklarasjon ---
// Opprett en instans av din sensorklasse
SoilMoistureSensor jordSensor("Plante-1", MOISTURE_PIN);

// Variabel for lagring av Adaptive Terskel
float currentAdaptiveThreshold = 0.0;


void setup() {
  Serial.begin(9600);
  Serial.println("Starter Jordfuktighetsmonitor...");
  
  // Initialiserer sensor-arrayene
  jordSensor.begin(); 
  
  // Gir tid til å stabilisere seg
  delay(1000); 
}

void loop() {
  // 1. Leser råverdi (filtrert med Exponential Moving Average)
  // Vi bruker EMA fordi den reagerer raskt nok, men jevner ut støy
  float filteredRawValue = jordSensor.exponentialMovingAverage();
  
  // 2. Oppdaterer den adaptive terskelen (denne metoden endrer også den interne terskelverdien)
  currentAdaptiveThreshold = jordSensor.adaptiveThreshold();
  
  // 3. Kalibrerer den filtrerte råverdien til en %-verdi (for menneskelig lesing)
  // Brukerer den filtrerte råverdien for å unngå at støy påvirker %-visningen
  int moisturePercent = map(filteredRawValue, DRY_CALIBRATION_VALUE, WET_CALIBRATION_VALUE, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);
  
  // --- Utskrift til Serial Monitor ---
  Serial.println("-------------------------------------");
  
  // Råverdi og %
  Serial.print("Fuktighet (Raa, EMA): ");
  Serial.print(filteredRawValue, 1);
  Serial.print(" | Fuktighet (%): ");
  Serial.print(moisturePercent);
  Serial.println("%");
  
  // Terskel
  Serial.print("Adaptive Terskel: ");
  Serial.print(currentAdaptiveThreshold, 1);
  Serial.println(" (Lavere = Vaatere)");
  
  // --- Varslingslogikk ---
  
  // Sjekker om den filtrerte råverdien overstiger den adaptive terskelen
  // Høy råverdi = Tørr jord
  if (filteredRawValue > currentAdaptiveThreshold) {
    // Varsling: Tørrere enn den adaptive terskelen 
    Serial.println("!!! ADVARSEL: JORDEN ER FOR TØRR !!!");
    Serial.println("!!! (rawVerdi > Adaptive Terskel) !!!");
  } 
  
  // Sjekker også for rask endring (f.eks. ved vanning eller plutselig tørke)
  int changeStatus = jordSensor.changeDetection();
  if (changeStatus == 1) {
    Serial.println("!!! RASK ENDRING MOT TØRRERE DETEKTERT !!!");
  }
  
  // Venter litt før neste avlesning
  delay(5000); 
}