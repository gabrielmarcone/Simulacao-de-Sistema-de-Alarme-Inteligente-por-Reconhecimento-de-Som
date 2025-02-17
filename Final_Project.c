#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "ws2812.pio.h"

// Definindo os pinos dos LEDs
#define LED_GREEN 11
#define LED_BLUE 12
#define LED_RED 13

// Variáveis para a matriz de LEDs
#define MATRIX_PIN 7
#define NUM_LEDS 25

// Definindo os pinos dos botões
#define BUTTON_A 5
#define BUTTON_B 6

// Definindo os pinos dos buzzers
#define BUZZER_A 10
#define BUZZER_B 21

// Definindo o pino para o microfone
#define MIC_PIN 28

// Variáveis para a comunicação I2C
#define I2C_PORT i2c1 // Porta I2C
#define I2C_SDA 14 // Pino para SDA
#define I2C_SCL 15 // Pino para SCL
#define SSD1306_ADDR 0x3C // Endereço do display OLED

int main() {
    stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}