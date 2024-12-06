//definicao do pino do sensor e de interrupcao
const int INTERRUPCAO_SENSOR = 0; //interrupt = 0 equivale ao pino digital 2
const int PINO_SENSOR_FLUXO = 2;

//definicao do fator de calibracao para conversao do valor lido
const float FATOR_CALIBRACAO = 4.5;

#ifndef FLOW_SENSOR_H
#define FLOW_SENSOR_H

void calc_flow(void);
void contador_pulso(void);

#endif