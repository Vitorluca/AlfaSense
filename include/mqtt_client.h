#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

#ifndef MQTT_CLIENT_H   // Protege o arquivo contra múltiplas inclusões
#define MQTT_CLIENT_H

extern WiFiClientSecure espClient;
extern PubSubClient client;

void setup_wifi();
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();

#endif