#include <ESP8266WiFi.h>
#include "WiFiManager.h"

const char* ssid = "Familia Ferreira";
const char* password = "021752565";

bool conectarWiFi() {
    WiFi.begin(ssid, password);

    unsigned long startAttemptTime = millis();

    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 15000) {
        delay(500);
        Serial.println("Conectando a WiFi " + String(ssid) + "...");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Conectado a WiFi: " + String(ssid));
        Serial.println("Dirección IP: " + WiFi.localIP().toString());
        return true;
    } else {
        Serial.println("Error al conectar a WiFi");
        return false;
    }
}
