#include <Arduino.h>
#include <ArduinoJson.h>
#include "Pines.h"
#include "WebsocketHandler.h"

void leerSensorPolvo() 
{
    unsigned long duracionLOW = 0;
    unsigned long duracionHIGH = 0;

    unsigned long empezarTiempo = millis();

    while (millis() - empezarTiempo < 1000) {
        int pinState = digitalRead(SENSOR_POLVO);

        unsigned long empezarPulso = micros();

        while (digitalRead(SENSOR_POLVO) == pinState) {
            if ((micros() - empezarPulso) > 1000000) break;
        }

        unsigned long duracionPulso = micros() - empezarPulso;

        if (pinState == LOW) {
            duracionLOW += duracionPulso;
        } else {
            duracionHIGH += duracionPulso;
        }
    }

    Serial.println("Duracion de HIGH en microsegundos:");
    Serial.println(duracionHIGH);
    Serial.println("Duracion de LOW en microsegundos:");
    Serial.println(duracionLOW);
}


