const int PINO_ONEWIRE = 12;  // Define pino do sensor

#ifndef TEMPERATURE_SENSOR_H   // Protege o arquivo contra múltiplas inclusões
#define TEMPERATURE_SENSOR_H

#include <OneWire.h>           // Inclui a biblioteca OneWire apenas uma vez
#include <DallasTemperature.h> // Inclui a biblioteca DallasTemperature apenas uma vez

// Objetos para sensor de temperatura
extern OneWire oneWire;       // Declara o objeto OneWire
extern DallasTemperature sensor;  // Declara o objeto DallasTemperature
extern DeviceAddress endereco_temp; // Declara o endereço temporário do sensor

void read_temperature(void);   // Declaração da função para ler a temperatura

#endif  // Fim da proteção contra múltiplas inclusões
