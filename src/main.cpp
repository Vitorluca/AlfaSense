#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#include "flow_sensor.h"
#include "temperature_sensor.h"

// #include "my_font.h" //fonte personalizada

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

    // display.print("Time:");
    // display.println(millis()/(1000*60*60)); //dado não é util

    display.print("SD:");
    display.println("--");

    display.display(); //star display

    calc_flow();
    read_temperature();

    delay(400);
    display.clearDisplay();
    display.setCursor(0, 0);  
}