/**
   @file main.cpp
   @brief Este é o arquivo principal do projeto
   
   @author Vitor Lucas
   @version 0.5
    @date 2024-12-06
   
   Este programa faz a conexão com WiFi e envia dados ao servidor MQTT.
 */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#include "flow_sensor.h"
#include "temperature_sensor.h"
#include "sd_card.h"
#include "mqtt_client.h"

#include "config.h"
#include "global_variables.h"


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define DHTTYPE DHT22
#define DHTPIN 4 

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

DHT dht(DHTPIN, DHTTYPE);

//usado para subistituir o delay
unsigned long startTime = millis();

void setup() {
  Serial.begin(115200);

  // Conecta à rede Wi-Fi
  setup_wifi();

  // Configura o servidor MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // Apenas para desenvolvimento; não use em produção
  espClient.setInsecure(); 

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("[SD_CARD] SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0); //(0,10)
  // Display static text
//   display.println("Hello, world!");
  display.display(); 

  Serial.println(F("[DHT22] inicializando dht22"));
  dht.begin();

  //mensagem de inicializacao
  Serial.println("[FLUX_SENSOR] inicializando sensor Fluxo e Volume de Liquidos\n");

  //configuracao do pino do sensor como entrada em nivel logico alto
  pinMode(PINO_SENSOR_FLUXO, INPUT_PULLUP);

  Serial.println("[TEMP_SENSOR] inicializando Medindo Temperatura"); // Imprime a mensagem inicial
  sensor.begin(); // Inicia o sensor


  //save sd card
  // Initialize SPI with defined pins
  SPI.begin(18, 19, 23, SD_CS_PIN);

  // Initialize SD card
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("[SD_CARD] Falha ao montar o cartão SD!");
    return;
  }

  uint8_t cardType = SD.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("[SD_CARD] Nenhum cartão SD encontrado");
    return;
  }

  Serial.print("[SD_CARD] Tipo de Cartão SD: ");
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
  Serial.printf("[SD_CARD] Tamanho do Cartão SD: %lluMB\n", cardSize);

  // Create and write header in the file if necessary
  File file = SD.open("/data_log.csv", FILE_READ);
  if (!file) {
    Serial.println("[SD_CARD] Criando arquivo data_log.csv...");
    writeFile(SD, "/data_log.csv", "humidade,temperatura_ambiente,fluxo, temperatura_agua");  // Header h, t, fluxo, temp_water
    
  } else {
    file.close();
  }
}

void loop() {
    delay(2000);

    float h = dht.readHumidity(); //humidade
    float t = dht.readTemperature(); //temperatura

    calc_flow(); //fluxo de agua
    read_temperature(); //temperatura da água


      // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("[DHT22] Failed to read from DHT sensor!"));
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
    display.print(h); //HUMIDADE
    display.println(F("%"));
    display.print("T: ");
    display.print(t); //TEMPERATURA
    display.println(F("C"));
    display.print("F: ");
    display.print(fluxo); //FLUXO DA AGUA
    display.println(" L/min");
    display.print("W: ");
    display.print(temp_water); //FLUXO DA AGUA
    display.println(" C");

    display.display(); //star display

    sprintf(buffer,"%.2f,%.2f,%.2f,%.2f", h, t, fluxo, temp_water);
    writeFile(SD, "/data_log.csv", buffer); // Save data AlfaSense
      
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
    
    // Publica humidade
    memset(buffer, 0, sizeof(buffer)); //zera buffer
    sprintf(buffer, "%.2f", h);
    client.publish("topic/humidade", buffer);

    // Publica temperatura ambiente
    memset(buffer, 0, sizeof(buffer)); //zera buffer
    sprintf(buffer, "%.2f", t);
    client.publish("topic/temp_ambiente", buffer);

    // Publica fluxo de agua
    memset(buffer, 0, sizeof(buffer)); //zera buffer
    sprintf(buffer, "%.2f", fluxo);
    client.publish("topic/fluxo", buffer);

    // Publica temperatura da agua
    memset(buffer, 0, sizeof(buffer)); //zera buffer
    sprintf(buffer, "%.2f", temp_water);
    client.publish("topic/temp_water", buffer);

    memset(buffer, 0, sizeof(buffer)); //zera buffer

    delay(400);

    display.clearDisplay();
    display.setCursor(0, 0);  
}