#include <Arduino.h>
#include "Pines.h"

void leerSensorPolvo() {

    unsigned long leerLow = pulseIn (sensorPolvo, LOW);
    unsigned long leerHigh = pulseIn (sensorPolvo, HIGH);
    
    Serial.println ("tiempo en LOW: " + String(leerLow) + " tiempo en HIGH: " + String(leerHigh));

    delay(1000);
}