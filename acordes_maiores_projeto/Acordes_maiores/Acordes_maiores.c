#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
#include "DHT.h"

#define DHT_PIN 15    // Pino conectado ao sensor DHT11
#define PINO_SDA 0    // Pino SDA para I2C
#define PINO_SCL 1    // Pino SCL para I2C
#define SSD1306_I2C_ADDRESS 0x3C // Endereço I2C do display OLED

DHT dht(DHT_PIN, DHT11); // Cria a instância do sensor DHT11
Adafruit_SSD1306 oled(128, 64, &i2c0, PINO_SDA, PINO_SCL, -1);

int main() {
    stdio_init_all();

    // Inicializa o I2C
    i2c_init(i2c0, 400000);  // 400kHz
    gpio_set_function(PINO_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PINO_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(PINO_SDA);
    gpio_pull_up(PINO_SCL);

    // Inicializa o display OLED
    if (!oled.begin(SSD1306_I2C_ADDRESS, 0x3C)) {
        printf("Falha ao inicializar o display OLED!\n");
        return -1;
    }

    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0, 0);

    // Inicializa o sensor DHT11
    dht.begin();

    while (1) {
        // Lê os valores de temperatura e umidade
        float t = dht.readTemperature();
        float h = dht.readHumidity();

        // Verifica se a leitura foi bem-sucedida
        if (isnan(t) || isnan(h)) {
            oled.clearDisplay();
            oled.setCursor(0, 0);
            oled.print("Erro ao ler o DHT11");
        } else {
            // Exibe os valores no display OLED
            oled.clearDisplay();
            oled.setCursor(0, 0);
            oled.print("Temperatura: ");
            oled.print(t);
            oled.print(" C\n");
            oled.print("Umidade: ");
            oled.print(h);
            oled.print(" %");
        }

        oled.display();  // Atualiza o display
        sleep_ms(2000);  // Aguarda 2 segundos antes da próxima leitura
    }

    return 0;
}