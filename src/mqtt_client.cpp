#include <Arduino.h>
#include "mqtt_client.h"
#include "config.h"

// Criação de um cliente WiFi e um cliente MQTT
// WiFiClient espClient;
WiFiClientSecure espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  // Conecta ao Wi-Fi
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Função de callback para lidar com mensagens recebidas
  Serial.print("Mensagem recebida [");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Conecta ao servidor MQTT
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    // Serial.println(mqtt_user);
    // Serial.println(mqtt_pass);
    if (client.connect("ESP32Client", mqtt_user, mqtt_pass)) {
      Serial.println("conectado");
      client.subscribe("topic/teste",1); // Se inscreva em um tópico
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}