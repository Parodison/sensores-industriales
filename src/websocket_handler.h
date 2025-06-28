#ifndef WEBSOCKET_MODULE_H
#define WEBSOCKET_MODULE_H

#include <Arduino.h>

void iniciar_websocket();
void websocket_loop();
void enviar_dato_websocket(const char* mensaje);

#endif