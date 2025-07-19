#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Pines.h"
#include "WiFiManager.h"
#include "WebsocketHandler.h"
#include "SensorAireHandler.h"
#include "SensorTemperaturaHandler.h"


void setup() {
  Serial.begin(9600);
  leerLeds();
  inicializarSensorTemperaturaHumedad();
  bool wifiConectado = conectarWiFi();
  if (wifiConectado) {
    conectarWebSocket();
  }
}

void loop() {
  websocketLoop();
  leerSensorAire();
  leerSensorTemperaturaHumedad();
}