#include <WebSocketsClient.h>

WebSocketsClient websocket;

void eventosWebSocket(WStype_t tipo, uint8_t * payload, size_t length) {
    switch (tipo) {
        case WStype_DISCONNECTED:
            Serial.println("Desconectado del servidor WebSocket");
            break;
        case WStype_CONNECTED:
            Serial.println("Conectado al servidor WebSocket");
            break;
        case WStype_TEXT:
            Serial.printf("Mensaje recibido: %s\n", payload);
            break;
        case WStype_BIN:
            Serial.printf("Datos binarios recibidos: %u bytes\n", length);
            break;
        default:
            break;
    }
}

void conectarWebSocket() {
    String path = "/api/sensores/ws?tipo=microcontrolador&token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJtaWNyb2NvbnRyb2xhZG9yIjoiU2Vuc29yIEluZHVzdHJpYWwifQ.0VXPDRG9ZBCgPfSiUstSfQ-SrTsKf5EpuBIhfceXFgc";
    websocket.begin("200.108.134.158", 8000, path.c_str());
    websocket.onEvent(eventosWebSocket);
    websocket.setReconnectInterval(5000);
}

void websocketLoop() {
    websocket.loop();
    
}

void enviarDatosWebSocket(const char* mensaje) {
    if (websocket.isConnected()) {
        websocket.sendTXT(mensaje);
    } else {
        Serial.println("No se puede enviar el mensaje, WebSocket no está conectado.");
    }
}
