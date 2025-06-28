#include <Arduino.h>
#include <wifi_connection.h>
#include <websocket_handler.h>

const char* ssid = "Familia Ferreira";
const char* password = "021752565";

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define PIN_SENSOR_AIRE A0

//PIN DEL LED 1
#define LED_ROJO D5

void setup() {
  Serial.begin(9600);
  bool wifi_conectado = conectar_a_wifi(ssid, password);

  if (wifi_conectado) {
    iniciar_websocket();
    pinMode(LED_ROJO, OUTPUT);
  }
}

unsigned long previousMillis = 0;
const long interval = 1000;
bool ledState = false;


void loop() {
    websocket_loop();
    /*
    unsigned long currentMillis = millis();
    
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        ledState = !ledState;

        digitalWrite(LED_ROJO, ledState ? HIGH : LOW);

        if (ledState) {
            enviar_dato_websocket("LED prendido");
        } else {
            enviar_dato_websocket("LED apagado");
        }
    }
    */

    int valor_sensor_aire = analogRead(PIN_SENSOR_AIRE);

    String mensaje = "Valor del sensor de aire: " + String(valor_sensor_aire);
    enviar_dato_websocket(mensaje.c_str());
    delay(500);
}
