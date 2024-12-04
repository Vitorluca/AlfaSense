#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#include "flow_sensor.h"
#include "temperature_sensor.h"
#include "sd_card.h"


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define DHTTYPE DHT22
#define DHTPIN 4 

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

DHT dht(DHTPIN, DHTTYPE);




void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
//   display.setFont(&myFont); // Usando a fonte personalizada
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0); //(0,10)
  // Display static text
//   display.println("Hello, world!");
  display.display(); 

  Serial.println(F("DHTxx test!"));
  dht.begin();

  //mensagem de inicializacao
  Serial.println("Medidor de Fluxo e Volume de Liquidos\n");

  //configuracao do pino do sensor como entrada em nivel logico alto
  pinMode(PINO_SENSOR_FLUXO, INPUT_PULLUP);

  Serial.println("Medindo Temperatura"); // Imprime a mensagem inicial
  sensor.begin(); // Inicia o sensor


  //save sd card
  // Initialize SPI with defined pins
  SPI.begin(18, 19, 23, SD_CS_PIN);

  // Initialize SD card
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("Falha ao montar o cartão SD!");
    return;
  }

  uint8_t cardType = SD.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("Nenhum cartão SD encontrado");
    return;
  }

  Serial.print("Tipo de Cartão SD: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("Desconhecido");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("Tamanho do Cartão SD: %lluMB\n", cardSize);

  // Create and write header in the file if necessary
  File file = SD.open("/data_log.csv", FILE_READ);
  if (!file) {
    Serial.println("Criando arquivo data_log.csv...");
    writeFile(SD, "/data_log.csv", "humidade,temperatura_ambiente,fluxo, temperatura_agua");  // Header h, t, fluxo, temp_water
    
  } else {
    file.close();
  }
}

void loop() {
    delay(2000);

    float h = dht.readHumidity();
    float t = dht.readTemperature();


      // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
    Serial.println('\n');
    Serial.print(F("Humidity: "));
    Serial.println(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.println(F("°C "));

    //print display oled 
    display.print("H: ");
    display.print(h);
    display.println(F("%"));
    display.print("T: ");
    display.print(t);
    display.println(F("C"));

    // display.print("SD:");
    // display.println("--");
    



    display.display(); //star display

    calc_flow();
    read_temperature();

    sprintf(buffer, "%.2f,%.2f,%.2f,%.2f", h, t, fluxo, temp_water);
    writeFile(SD, "/data_log.csv", buffer); // Save data AlfaSense

    delay(400);
    display.clearDisplay();
    display.setCursor(0, 0);  
}