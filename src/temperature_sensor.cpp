#include <Arduino.h>
#include "temperature_sensor.h"
#include "global_variables.h"

// Definição dos objetos e variáveis globais
OneWire oneWire(PINO_ONEWIRE);         // Cria o objeto OneWire com o pino configurado
DallasTemperature sensor(&oneWire);    // Cria o objeto DallasTemperature com o objeto OneWire
DeviceAddress endereco_temp;           // Define o endereço do sensor (o endereço específico)

void read_temperature(){
    sensor.requestTemperatures(); // Envia comando para realizar a conversão de temperatura
  if (!sensor.getAddress(endereco_temp,0)) { // Encontra o endereco do sensor no barramento
    Serial.println("SENSOR NAO CONECTADO"); // Sensor conectado, imprime mensagem de erro
  } else {
    Serial.print("Temperatura = "); // Imprime a temperatura no monitor serial
    Serial.println(sensor.getTempC(endereco_temp), 1); // Busca temperatura para dispositivo
    temp_water = sensor.getTempC(endereco_temp);
  }
  delay(1000);
}