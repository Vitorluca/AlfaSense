#include <Arduino.h>
#include "flow_sensor.h"

//definicao das variaveis de fluxo e volume
float fluxo = 0;
float volume = 0;
float volume_total = 0;

//definicao da variavel de contagem de voltas
unsigned long contador = 0;

//definicao da variavel de intervalo de tempo
unsigned long tempo_antes = 0;


void calc_flow(){
     //executa a contagem de pulsos uma vez por segundo
    if((millis() - tempo_antes) > 1000){

        //desabilita a interrupcao para realizar a conversao do valor de pulsos
        detachInterrupt(INTERRUPCAO_SENSOR);

        //conversao do valor de pulsos para L/min
        fluxo = ((1000.0 / (millis() - tempo_antes)) * contador) / FATOR_CALIBRACAO;

        //exibicao do valor de fluxo
        Serial.print("Fluxo de: ");
        Serial.print(fluxo);
        Serial.println(" L/min");

        //calculo do volume em L passado pelo sensor
        volume = fluxo / 60;

        //armazenamento do volume
        volume_total += volume;

        //exibicao do valor de volume
        Serial.print("Volume: ");
        Serial.print(volume_total);
        Serial.println(" L");
        Serial.println();

        //reinicializacao do contador de pulsos
        contador = 0;

        //atualizacao da variavel tempo_antes
        tempo_antes = millis();

        //contagem de pulsos do sensor
        attachInterrupt(INTERRUPCAO_SENSOR, contador_pulso, FALLING);
    
  }
}

void contador_pulso() {
  
  contador++;
  
}