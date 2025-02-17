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

// Variável limite para o microfone
#define MIC_LIMIT 2500

// Função para iniciar os pinos GPIO
void init_gpio() {
    // Inicializando os pinos dos LEDs
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);

    // Inicializando os pinos dos botões
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);

    // Inicializando os pinos dos buzzers
    gpio_init(BUZZER_A);
    gpio_set_dir(BUZZER_A, GPIO_OUT);
    gpio_init(BUZZER_B);
    gpio_set_dir(BUZZER_B, GPIO_OUT);

    // Inicializa as funções ADC
    adc_init();
    adc_gpio_init(MIC_PIN);

    // Inicialização do I2C
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Define a função do pino GPIO para I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Define a função do pino GPIO para I2C
    gpio_pull_up(I2C_SDA); // Resistor de pull-up para o pino de dados
    gpio_pull_up(I2C_SCL); // Resistor de pull-up para o pino de clock
}

int main() {
    stdio_init_all();
    init_gpio();

    while (true) {
        adc_select_input(2); // Seleciona o ADC para o microfone. O pino 28 como entrada analógica
        uint16_t mic_value = adc_read();
        printf("Microphone: %d\n", mic_value);

        if (mic_value > MIC_LIMIT) {
            gpio_put(LED_GREEN, 1);
            gpio_put(LED_BLUE, 1);
            gpio_put(LED_RED, 1);
            sleep_ms(1000);
        } else {
            gpio_put(LED_GREEN, 0);
            gpio_put(LED_BLUE, 0);
            gpio_put(LED_RED, 0);
        }
    }
}