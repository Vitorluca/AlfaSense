//definicao do pino do sensor e de interrupcao
const int INTERRUPCAO_SENSOR = 14; //interrupt = 0 equivale ao pino digital 2
const int PINO_SENSOR_FLUXO = 14;

//definicao do fator de calibracao para conversao do valor lido
const float FATOR_CALIBRACAO = 4.5;

#ifndef FLOW_SENSOR_H
#define FLOW_SENSOR_H

void calc_flow(void);
void contador_pulso(void);

#endif