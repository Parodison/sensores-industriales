#include <Arduino.h>
#include "Pines.h"

void leerLeds() {
    pinMode(LED_ROJO, OUTPUT);
    pinMode(LED_AMARILLO, OUTPUT);
    pinMode(LED_AZUL, OUTPUT);
    pinMode(BUZZER, OUTPUT);
}

void configurarSensorPolvo() {
    pinMode(SENSOR_POLVO, INPUT);
    }