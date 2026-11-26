# ESP32 MultiTool

Ferramenta portátil de experimentação com redes sem fio e sistemas embarcados, baseada no ESP32.

## Objetivo
Explorar a integração entre interfaces físicas, comunicação sem fio e programação embarcada para fins educacionais.

## Funcionalidades previstas no firmware
- Menu OLED com quatro botões.
- Listagem de redes Wi-Fi, canais e intensidade de sinal (RSSI).
- Observação de anúncios Bluetooth Low Energy e RSSI.
- Consulta de informações de hardware e memória.

## Tecnologias
ESP32 DevKit V1, C++ (Arduino), SSD1306 I2C, Adafruit GFX e Adafruit SSD1306.

## Instalação
1. Instale a Arduino IDE e o pacote de placas esp32 da Espressif (versão 3.x).
2. Instale as bibliotecas Adafruit GFX Library e Adafruit SSD1306.
3. Monte o circuito conforme [hardware.md](docs/hardware.md).
4. Abra `firmware/multitool/multitool.ino`, selecione ESP32 Dev Module e a porta serial e compile e envie.
5. Use UP/DOWN para navegar, OK para selecionar e BACK para retornar. As varreduras podem levar alguns segundos.

## Contribuição e processo
O projeto retoma uma iniciativa pessoal de experimentação com ESP32, menus físicos e redes sem fio. Esta versão foi reconstruída com auxílio de IA a partir das funcionalidades planejadas anteriormente. A montagem, validação e revisão do firmware são etapas a realizar.

## Evidências
Validação física pendente. Após testar, adicionar fotografias da montagem, do menu e das telas de resultados em `images/`, evitando expor identificadores de redes ou dispositivos de terceiros.

## Estado atual
Protótipo V1.0: código reconstruído, ainda não compilado nem testado em hardware. Uso educacional em ambientes autorizados; não realiza interferência nem conexão às redes detectadas.

## Próximos passos
- Validar compilação e funcionamento no ESP32.
- Registrar evidências reais.
- Estudar integração futura dos módulos CC1101 e NRF24L01.

## Licença
MIT.
