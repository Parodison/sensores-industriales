#include <Arduino.h>
#include <ArduinoJson.h>
#include "Pines.h"
#include "WebsocketHandler.h"

unsigned long lowStart = 0;
unsigned long lowPulseOccupancy = 0;
unsigned long sampleStartTime = 0;
const unsigned long sampleTimeMs = 30000;

bool wasLow = false;

const float correctionFactor = 0.05;  // Ajusta si calibras con sensor de referencia

void inicializarSensorPolvo() {
  sampleStartTime = millis();
  Serial.println("[DSM501B] Inicializado.");
}

void leerSensorPolvo() {
  unsigned long now = millis();
  int val = digitalRead(sensorPolvo);

  if (val == LOW) {
    if (!wasLow) {
      lowStart = micros();  // empieza pulso LOW
      wasLow = true;
    }
  } else {
    if (wasLow) {
      unsigned long pulseLength = micros() - lowStart;
      if (pulseLength > 100) {
        lowPulseOccupancy += pulseLength;
      }
      wasLow = false;
    }
  }

  if ((now - sampleStartTime) >= sampleTimeMs) {
    float ratio = lowPulseOccupancy / (sampleTimeMs * 10.0);  
    float concentrationRaw = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62;
    float concentrationCorr = concentrationRaw * correctionFactor;
    float pm25Corr = concentrationCorr * 0.075;

    Serial.println("------ RESULTADOS DSM501B ------");
    Serial.print("Low Pulse Occupancy (us): ");
    Serial.println(lowPulseOccupancy);
    Serial.print("Ratio (%): ");
    Serial.println(ratio, 2);
    Serial.print("Concentración bruta (pcs/0.01cf): ");
    Serial.println(concentrationRaw, 2);
    Serial.print("Concentración corregida (pcs/0.01cf): ");
    Serial.println(concentrationCorr, 2);
    Serial.print("PM2.5 corregido (µg/m³): ");
    Serial.println(pm25Corr, 2);
    Serial.println("--------------------------------\n");

    lowPulseOccupancy = 0;
    sampleStartTime = now;

    StaticJsonDocument<200> jsonData; 
    jsonData["operacion"] = "enviar_datos_sensor";
    JsonObject datos = jsonData.createNestedObject("datos");
    datos["sensor"] = "polvo";
    datos["valor"] = round(pm25Corr * 100) / 100.0;

    String JsonString;
    serializeJson(jsonData, JsonString);
    
    enviarDatosWebSocket(JsonString.c_str());

  }
}