#include <Arduino.h>
#include <ArduinoJson.h>
#include "Pines.h"
#include "WebsocketHandler.h"

static int ppmActual = 0;

void leerSensorAire() {

    static unsigned long ultimaLectura = 0;
    static unsigned long intervaloLectura = 3000;
    if (millis() - ultimaLectura >= intervaloLectura) {
        ultimaLectura = millis();

        int ppmLeido = analogRead(SENSOR_AIRE);
        if (ppmActual != ppmLeido) {
            ppmActual = ppmLeido;
            
            if (ppmLeido <= 350) {
                Serial.println("Aire limpio " + String(ppmLeido));
                digitalWrite(LED_AZUL, HIGH);
                digitalWrite(LED_AMARILLO, LOW);
                digitalWrite(LED_ROJO, LOW);
                digitalWrite(BUZZER, LOW);
            }
            if (ppmLeido <= 550 && ppmLeido > 350) {
                Serial.println("Aire moderadamente contaminado " + String(ppmLeido));
                digitalWrite(LED_AMARILLO, HIGH);
                digitalWrite(LED_AZUL, LOW);
                digitalWrite(LED_ROJO, LOW);
                digitalWrite(BUZZER, LOW);
            }
            if (ppmLeido > 550) {
                Serial.println("Aire contaminado " + String(ppmLeido));
                digitalWrite(LED_ROJO, HIGH);
                digitalWrite(LED_AZUL, LOW);
                digitalWrite(LED_AMARILLO, LOW);
                digitalWrite(BUZZER, LOW); 
            }

            StaticJsonDocument<200> doc;
            doc["operacion"] = "enviar_datos_sensor";
            JsonObject datos = doc.createNestedObject("datos");
            datos["sensor"] = "aire";
            datos["valor"] = ppmLeido;

            String jsonString;
            serializeJson(doc, jsonString);
            
            enviarDatosWebSocket(jsonString.c_str());

        }
        
    }
}