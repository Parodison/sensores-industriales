#include <WebSocketsClient.h>

WebSocketsClient websocket;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_CONNECTED:
            Serial.println("WebSocket conectado");
            websocket.sendTXT("ESP8266 conectado");
            break;
        case WStype_DISCONNECTED:
            Serial.println("WebSocket desconectado");
            break;
        case WStype_TEXT:
            break;
        case WStype_BIN:
            Serial.println("Mensaje binario recibido");
            break;
        case WStype_FRAGMENT_TEXT_START:
        case WStype_FRAGMENT_BIN_START:
        case WStype_FRAGMENT:
        case WStype_FRAGMENT_FIN:
            break;
        case WStype_ERROR:
            Serial.println("Error WebSocket");
            break;
        case WStype_PING:
        case WStype_PONG:
            // Opcional manejar ping/pong
            break;
    }
}


void iniciar_websocket() {
    websocket.begin("192.168.100.31", 8000, "/ws");
    websocket.onEvent(webSocketEvent);
    websocket.setReconnectInterval(5000);
}

void websocket_loop() {
    websocket.loop();
}

void enviar_dato_websocket(const char* mensaje) {
    if (websocket.isConnected()) {
        Serial.println(mensaje);
        websocket.sendTXT(mensaje);
    } else {
        Serial.println("WS no conectado, no se envió mensaje");
    }
}