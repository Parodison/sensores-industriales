#include <ESP8266WiFi.h>

bool conectar_a_wifi(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println(String("Conectando a la red WiFi... ") + ssid);
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConectado a WiFi!");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        return true;
    } else {
        Serial.println("\nError: No se pudo conectar a WiFi");
        return false;
    }
}