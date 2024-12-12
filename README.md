# AlfaSense

O **AlfaSense** é um sistema inteligente desenvolvido para monitorar e otimizar as condições de um cultivo hidropônico de alface. Utilizando sensores avançados, o sistema coleta dados essenciais, como temperatura, umidade e fluxo de água, para garantir que as plantas recebam as condições ideais para seu crescimento. Com automação e análise desses dados em tempo real, o **AlfaSense** proporciona uma gestão eficiente, sustentável e de baixo custo para sistemas de cultivo hidropônico.

---

## Project Description

### 1. Requisitos do Projeto

- [Sensor de Temperatura e Umidade (DHT22)](https://blog.eletrogate.com/sensores-dht11-dht22/)
- [Cartão SD](https://blog.eletrogate.com/gravacao-de-cartao-micro-sd-com-arduino/)
- [Sensor de Fluxo de Água](https://www.robocore.net/tutoriais/usando-sensor-fluxo-de-agua?srsltid=AfmBOop5U_WtSI5_IvKNNCcCxQMp0dhDSsZdoMKUAfDzZMoC_m_Guo6d)
- [Sensor de Tempertura da água](https://www.robocore.net/tutoriais/primeiros-passos-ds18b20-arduino?srsltid=AfmBOopOh0tPdRKgMwcXEHIK44C2FYUGw6nCdGaH6_7ZIXtDBWHG8kre)
- [Display](https://www.makerhero.com/blog/como-conectar-display-oled-arduino/)
- [Notificação via celular](https://iotguru.cloud/tutorials/mqttPanel)
- [Alimentação](https://www.usinainfo.com.br/fonte-chaveada-usb-e-p4/fonte-chaveada-5v-34a-2-x-17a-usb-dupla-para-arduino-esp32-e-celular-branca-6026.html)

### 2. Teste de Componentes Separadamente

- Verificar o funcionamento individual de cada sensor e componente do sistema.
- Realizar testes de comunicação e leitura de dados para garantir precisão.

### 3. Integração

- Conectar e integrar todos os sensores e componentes no sistema.
- Configurar a comunicação entre os dispositivos (ex.: sensor, microcontrolador e display).

### 4. Debug

- Realizar o processo de depuração para identificar e corrigir erros no código e na integração dos componentes.
- Garantir que todos os sensores e componentes funcionem corretamente.

### 5. Finalização

- Ajustes finais na programação e nos parâmetros do sistema.
- Verificação de desempenho e otimização do sistema para uso real.
- Testes finais para garantir a estabilidade e a funcionalidade do sistema.


## Lista de Portas GPIO Utilizadas

### 1. SD card(SPI)

- 18 (SCK)
- 19 (MISO)
- 23 (MOSI)
- 5 (CS)
- GND
- 5V

### 2. Sensor Temperatura água

- GND
- 5V
- 12 (DATA)

### 3. Sensor de Fluxo

- GND
- 5V
- 15 (DATA)

### 4. Sensor DHT22

- GND
- 5V
- 4 (DATA)

### 5. Display (I2C)

- 21 (SDA)
- 22 (SCL)
- GND
- 3.3V

