#pragma once
#include <Arduino.h>

#define LED_ROJO D3
#define LED_AMARILLO D6
#define LED_AZUL D5
#define SENSOR_AIRE A0
#define SENSOR_TEMPERATURA_HUMEDAD D4
#define BUZZER D7


const int sensorPolvo = D8;

void leerSensorPolvo();

void inicializarPines();