#include <Arduino.h>
#include <DHT.h>
#include <ArduinoJson.h>
#include "Pines.h"
#include "WebsocketHandler.h"

#define DHTTYPE DHT11

DHT dht(SENSOR_TEMPERATURA_HUMEDAD, DHTTYPE);

void inicializarSensorTemperaturaHumedad()
{
    dht.begin();
    Serial.print("Sensor temperatura y humedad inicializado");
}

int temperaturaActual = 0;
int humedadActual = 0;

void enviarHumedadTemperatura(float humedad, float temperatura)
{
    StaticJsonDocument<200> doc_temperatura;

    doc_temperatura["operacion"] = "enviar_datos_sensor";
    JsonObject datos = doc_temperatura.createNestedObject("datos");

    datos["sensor"] = "temperatura";
    datos["valor"] = temperatura;

    StaticJsonDocument<200> doc_humedad;
    doc_humedad["operacion"] = "enviar_datos_sensor";
    JsonObject datos_humedad = doc_humedad.createNestedObject("datos");
    datos_humedad["sensor"] = "humedad";
    datos_humedad["valor"] = humedad;

    String json_temperatura;
    serializeJson(doc_temperatura, json_temperatura);
    String json_humedad;
    serializeJson(doc_humedad, json_humedad);

    enviarDatosWebSocket(json_temperatura.c_str());
    enviarDatosWebSocket(json_humedad.c_str());
}

void leerSensorTemperaturaHumedad()
{
    float temperatura = dht.readTemperature();
    float humedad = dht.readHumidity();

    static unsigned long ultimaLectura = 0;
    static unsigned long intervaloLectura = 10000;
    if (millis() - ultimaLectura >= intervaloLectura)
    {
        ultimaLectura = millis();

        if (isnan(temperatura) || isnan(humedad))
        {
            Serial.println("Error al leer temperatura y humedad");
        }

        if (temperatura != temperaturaActual || humedad != humedadActual)
        {
            temperaturaActual = temperatura;
            humedadActual = humedad;
            Serial.print("Temperatura: ");
            Serial.print(temperatura);
            Serial.print("°C ");
            Serial.print(" Humedad: ");
            Serial.print(humedad);
            Serial.println("%");

            enviarHumedadTemperatura(humedad, temperatura);
        }
    }
}
