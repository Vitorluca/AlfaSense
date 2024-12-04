#include <Arduino.h>
#include "sd_card.h"

void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Escrevendo arquivo: %s\n", path);

  File file = fs.open(path, FILE_APPEND);  // FILE_APPEND para não sobrescrever
  if(!file){
    Serial.println("Falha ao abrir o arquivo para escrita");
    return;
  }
  if(file.println(message)){
    Serial.println("Arquivo gravado com sucesso");
  } else {
    Serial.println("Falha na gravação");
  }
  file.close();
}