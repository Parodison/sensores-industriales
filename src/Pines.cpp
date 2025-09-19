#include <Arduino.h>
#include "Pines.h"

void inicializarPines() {
    pinMode(LED_ROJO, OUTPUT);
    pinMode(LED_AMARILLO, OUTPUT);
    pinMode(LED_AZUL, OUTPUT);
    pinMode(BUZZER, OUTPUT);

    pinMode (sensorPolvo, INPUT);
}