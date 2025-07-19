#pragma once
#include <WebSocketsClient.h>

void conectarWebSocket();
void websocketLoop();
void eventosWebSocket(WStype_t tipo, uint8_t * payload, size_t length); 
void enviarDatosWebSocket(const char* mensaje);