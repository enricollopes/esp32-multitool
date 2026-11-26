# Montagem

| Componente | ESP32 DevKit V1 |
|---|---|
| OLED VCC | 3V3 |
| OLED GND | GND |
| OLED SDA | GPIO 21 |
| OLED SCL | GPIO 22 |
| UP | GPIO 5 |
| DOWN | GPIO 18 |
| OK | GPIO 23 |
| BACK | GPIO 19 |

Conecte cada botão entre o GPIO indicado e GND. O firmware utiliza INPUT_PULLUP. Não mantenha o botão UP pressionado durante a inicialização, pois GPIO 5 é um pino de configuração de boot. Display previsto: SSD1306 128x64, endereço 0x3C. Desligue a alimentação antes de alterar a montagem.
