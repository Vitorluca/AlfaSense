const int SD_CS_PIN = 5; // Pino CS (Chip Select) para o cartão SD

#include "FS.h"
#include "SD.h"
#include "SPI.h"

#ifndef SD_CARD_H  // Protege o arquivo contra múltiplas inclusões
#define SD_CARD_H

// Objetos para sensor de temperatura
void writeFile(fs::FS &fs, const char * path, const char * message);

#endif  // Fim da proteção contra múltiplas inclusões
