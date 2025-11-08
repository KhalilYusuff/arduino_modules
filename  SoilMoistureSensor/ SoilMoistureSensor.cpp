#include "SoilMoistureSensor.h"
#include <algorithm> // Trengs for std::sort (brukes i medianFilter)

// --- Initialisering ---

// Konstruktør – Initialiserer private felt
SoilMoistureSensor::SoilMoistureSensor(String nName, int pin) 
    : name(nName), analogPin(pin) 
{

}

// Setter opp array for Moving Average
void SoilMoistureSensor::begin() {
    for (int i = 0; i < WINDOW_SIZE; i++) {
        readings[i] = 0;
    }
}

// Hjelpemetode
String SoilMoistureSensor::getName() {
    return name;
}

// --- Grunnleggende Lesing og Kalibrering 

int SoilMoistureSensor::readRawValue() {
    int rawValue = analogRead(this->analogPin);
    return rawValue;
}

int SoilMoistureSensor::calibrateSensor(int minValue, int maxValue) {
    int rawValue = readRawValue();

    int moisture = map(rawValue, minValue, maxValue, 0, 100);

    moisture = constrain(moisture, 0, 100);

    return moisture;
}

// --- Signalbehandling ---

/**
 * Rullerende gjennomsnitt. Returnerer et jevnere signal.
 * Hver gang den kalles, legges en ny råverdi til i et rullerende vindu (readings).
 */
int SoilMoistureSensor::movingAverage() {
    int rawValue = readRawValue();
    
    // Legg til ny lesing og flytt indeksen
    readings[readIndex] = rawValue;
    readIndex = (readIndex + 1) % WINDOW_SIZE; 

    long total = 0;
    for (int i = 0; i < WINDOW_SIZE; i++) {
        total += readings[i];
    }
    
    return total / WINDOW_SIZE;
}

/**
 * Medianfilter for å fjerne enkeltstående støy-pigger ("outliers").
 */
int SoilMoistureSensor::medianFilter() {
    // 1. Les ny verdi og oppdater arrayet (samme som Moving Average)
    readings[readIndex] = readRawValue();
    readIndex = (readIndex + 1) % WINDOW_SIZE; 
    
    // 2. Kopier arrayet for å sortere det (sortering endrer originaldata)
    int tempReadings[WINDOW_SIZE];
    for(int i=0; i<WINDOW_SIZE; i++) {
        tempReadings[i] = readings[i];
    }
    
    // 3. Sorter den midlertidige arrayen
    std::sort(tempReadings, tempReadings + WINDOW_SIZE);
    
    // 4. Returner medianen (midterste element)
    return tempReadings[WINDOW_SIZE / 2];
}

/**
 * Eksponentielt Glidende Gjennomsnitt (EMA). Vektlegger nyere data mer.
 */
float SoilMoistureSensor::exponentialMovingAverage() {
    int rawValue = readRawValue();
    
    if (EMA_value == 0.0) {
        // Initialiser EMA_value ved første kall
        EMA_value = (float)rawValue;
    } else {
        // Beregn nytt EMA: NewEMA = (RawValue * Alpha) + (OldEMA * (1 - Alpha))
        EMA_value = (rawValue * EMA_ALPHA) + (EMA_value * (1.0 - EMA_ALPHA));
    }
    return EMA_value;
}

// --- Avanserte Funksjoner ---

/**
 * Implementerer en dynamisk terskel basert på siste EMA-verdi.
 * Hvis den målte fuktigheten er mye lavere enn den adaptive terskelen,
 * justeres terskelen sakte ned for å tilpasse seg sensorens degradering.
 *
 * Returnerer den gjeldende dynamiske terskelen.
 */
float SoilMoistureSensor::adaptiveThreshold() {
    // Bruk den jevne EMA-verdien for å unngå at støy påvirker terskelen for mye
    float currentEMA = exponentialMovingAverage(); 
    
    // Anta at 700 er en 'tørr' råverdi for denne sensoren.
    // Vi ønsker at terskelen skal ligge litt under denne verdien.
    float targetThreshold = currentEMA + 50; // Ønsket terskel er litt over EMA
    
    // Hvis sensoren degraderer (EMA stiger for tørr jord), 
    // vil vi la terskelen følge etter, men sakte.
    if (currentEMA > adaptiveThresholdValue) {
        // Juster terskelen sakte oppover
        adaptiveThresholdValue += THRESHOLD_ADJUST_RATE * (currentEMA - adaptiveThresholdValue);
    } 
    // Hvis jorden blir våt igjen, la terskelen synke raskt tilbake
    else if (currentEMA < adaptiveThresholdValue - 100) { 
        adaptiveThresholdValue = currentEMA + 50; 
    }
    
    // Sørg for at terskelen har en minimumsverdi for å unngå feilvarsler
    if (adaptiveThresholdValue < 500) {
        adaptiveThresholdValue = 500;
    }
    
    return adaptiveThresholdValue;
}

/**
 * Detekterer om den siste råverdien er betydelig annerledes enn EMA.
 * Returnerer 1 hvis det er en stor endring, 0 ellers.
 * Kan brukes til å varsle om at jorden er for tørr.
 */
int SoilMoistureSensor::changeDetection() {
    float currentEMA = exponentialMovingAverage();
    int rawValue = readRawValue();
    
    // Sett en statisk/konstant endringsterskel. F.eks. 15% av råverdiområdet (1023)
    const int CHANGE_THRESHOLD = 150; 

    // Sjekk for rask endring. Er råverdien MYE høyere enn gjennomsnittet (tørrere)?
    if (rawValue > (currentEMA + CHANGE_THRESHOLD)) {
        // Veldig rask endring mot tørrere – indikerer en mulig "tørke-hendelse"
        return 1; 
    }
    
    // Sjekk om fuktigheten er under den dynamiske terskelen
    if (rawValue > adaptiveThreshold()) {
        // Råverdien (tørrere) er over den adaptive grensen (våtere)
        return 2; 
    }

    return 0; // Ingen signifikant endring
}