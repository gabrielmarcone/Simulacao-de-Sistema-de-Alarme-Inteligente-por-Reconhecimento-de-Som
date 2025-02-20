#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/pio.h"
#include "hardware/timer.h" //
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "ws2812.pio.h"
#include "lib/ssd1306.h"
#include "lib/font.h"
#include "animations.h"

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
ssd1306_t ssd; // Estrutura para o display OLED

// Variáveis globais para o controle PIO
static PIO  pio = pio0;
static uint sm  = 0;

// Variável limite para o microfone
#define MIC_LIMIT 3000

// Variáveis para controle de PWM
#define PWM_DIVISER 30.0 // Divisor de clock para PWM
#define WRAP_VALUE 4096 // WRAP para o microfone
volatile bool pwm_enabled = false; // Estado do PWM (se ativado ou não)

// Debounce time
#define DEBOUNCE_TIME 200  // 200 ms

// Estado dos botões
volatile uint32_t last_press_time_A = 0;
volatile uint32_t last_press_time_B = 0;

volatile bool alarm_triggered = false; // Estado do alarme (se disparado ou não)

uint16_t last_mic_value = 0; // Variável para armazenar a última leitura do microfone

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

// Função para configurar o módulo PWM
void pwm_setup() {
    // Configura o PWM para o LED verde
    gpio_set_function(LED_GREEN, GPIO_FUNC_PWM);
    uint slice_led_green = pwm_gpio_to_slice_num(LED_GREEN);
    pwm_set_clkdiv(slice_led_green, PWM_DIVISER);
    pwm_set_wrap(slice_led_green, WRAP_VALUE);
    pwm_set_enabled(slice_led_green, true);

    // Configura o PWM para o LED Vermelho
    gpio_set_function(LED_RED, GPIO_FUNC_PWM);
    uint slice_led_red = pwm_gpio_to_slice_num(LED_RED);
    pwm_set_clkdiv(slice_led_red, PWM_DIVISER);
    pwm_set_wrap(slice_led_red, WRAP_VALUE);
    pwm_set_enabled(slice_led_red, true);

    // Configura o PWM para o Buzzer A
    gpio_set_function(BUZZER_A, GPIO_FUNC_PWM);
    uint slice_buzzer_A = pwm_gpio_to_slice_num(BUZZER_A);
    pwm_set_clkdiv(slice_buzzer_A, PWM_DIVISER);
    pwm_set_wrap(slice_buzzer_A, WRAP_VALUE);
    pwm_set_enabled(slice_buzzer_A, true);

    // Configura o PWM para o Buzzer B
    gpio_set_function(BUZZER_B, GPIO_FUNC_PWM);
    uint slice_buzzer_B = pwm_gpio_to_slice_num(BUZZER_B);
    pwm_set_clkdiv(slice_buzzer_B, PWM_DIVISER);
    pwm_set_wrap(slice_buzzer_B, WRAP_VALUE);
    pwm_set_enabled(slice_buzzer_B, true);
}

// Função para definir brilho dos LEDs com base no microfone (somente se o PWM estiver ativado)
void set_led_intensity(uint16_t mic_value) {
    if (pwm_enabled) {
        uint16_t intensity = abs(mic_value - 2048) * 2;  // Controla a intensidade dos leds

        // Define o nível de PWM para os LEDs
        pwm_set_gpio_level(LED_GREEN, intensity);
        pwm_set_gpio_level(LED_RED, intensity);
    } else {
        // Se o PWM estiver desativado, mantém o led verde aceso e o vermelho apagado
        pwm_set_gpio_level(LED_GREEN, WRAP_VALUE);
        pwm_set_gpio_level(LED_RED, 0);
    }
}

void update_display() {
    char mic_value_str[16];
    snprintf(mic_value_str, sizeof(mic_value_str), "MIC: %d", last_mic_value);

    ssd1306_fill(&ssd, false);
    ssd1306_draw_string(&ssd, "SYSTEM STATUS:", 8, 5);
    ssd1306_draw_string(&ssd, "---------------", 4, 12);
    if (alarm_triggered) {
        ssd1306_draw_string(&ssd, "ALARME", 37, 30);
        ssd1306_draw_string(&ssd, "DISPARADO!", 26, 40);
    } else if (pwm_enabled) {
        ssd1306_draw_string(&ssd, "ALARME: ON", 20, 30);
        ssd1306_draw_string(&ssd, "---------------", 4, 45);
        ssd1306_draw_string(&ssd, mic_value_str, 25, 55);
    } else {
        ssd1306_draw_string(&ssd, "ALARME: OFF", 20, 30);
    }
    ssd1306_send_data(&ssd);
}

// Função para converter a intensidade de cada canal G, R, B em 24 bits
uint32_t matrix_rgb(double g, double r, double b) {
    unsigned char G = (unsigned char)(g * 255.0);
    unsigned char R = (unsigned char)(r * 255.0);
    unsigned char B = (unsigned char)(b * 255.0);

    return ( (uint32_t)G << 24 ) |
           ( (uint32_t)R << 16 ) |
           ( (uint32_t)B <<  8 );
}

void clear_all_leds() {
    for (int i = 0; i < NUM_LEDS; i++) {
        pio_sm_put_blocking(pio, sm, 0); // Desliga todos os LEDs
    }
}

// Envia UM quadro (25 pixels)
static void draw_frame(const uint32_t frame[NUM_LEDS]) {
    for (int i = 0; i < NUM_LEDS; i++) {
        pio_sm_put_blocking(pio, sm, frame[i]);
    }
    sleep_us(80); // Pausa para garantir que os LEDs processam os dados
}

// Roda uma animação de `num_frames` quadros; cada quadro tem 25 LEDs.
void run_animation(const uint32_t frames[][NUM_LEDS], int num_frames, int delay_ms) {
    for (int i = 0; i < num_frames; i++) {
        draw_frame(frames[i]); // Envia o quadro atual
        sleep_ms(delay_ms);    // Espera o tempo especificado antes do próximo quadro
    }
}

void update_matrix_leds() {
    if (pwm_enabled) {
        clear_all_leds();
        return;
    } else {
        animation_alarm_off();
    }
}

void play_siren() {
    alarm_triggered = true;
    update_display();
    const uint16_t levels[] = {WRAP_VALUE, 3000, 2000, 1000, 500, 1000, 2000, 3000, WRAP_VALUE, 0};
    const uint16_t buzz_levels[] = {WRAP_VALUE / 2, WRAP_VALUE / 4, WRAP_VALUE / 6, WRAP_VALUE / 8,
                                    WRAP_VALUE / 10, WRAP_VALUE / 8, WRAP_VALUE / 6, WRAP_VALUE / 4,
                                    WRAP_VALUE / 2, 0};

    pwm_set_gpio_level(LED_GREEN, 0);

    while (alarm_triggered) {
        animation_alarm_triggered();
        for (int i = 0; i < 10 && alarm_triggered; i++) {
            pwm_set_gpio_level(BUZZER_A, buzz_levels[i]);
            pwm_set_gpio_level(BUZZER_B, buzz_levels[i]);
            pwm_set_gpio_level(LED_RED, levels[i]);
            
            sleep_ms(50);
        }
    }
    // Desliga LEDs e buzzers após o alarme ser interrompido
    pwm_set_gpio_level(BUZZER_A, 0);
    pwm_set_gpio_level(BUZZER_B, 0);
    pwm_set_gpio_level(LED_RED, 0);
    clear_all_leds();
}

// Callback para interrupções dos botões
void button_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    if (gpio == BUTTON_A) { // Aciona/Desliga o sistema de Alarme
        if (current_time - last_press_time_A > DEBOUNCE_TIME * 1000) { // Debounce
            last_press_time_A = current_time;  // Atualiza o tempo da última pressão

            pwm_enabled = !pwm_enabled; // Alterna o estado do PWM
            clear_all_leds();
            update_display();
            printf("Botão A pressionado. Sistema Ativo: %d\n", pwm_enabled);
        }
    } 
    else if (gpio == BUTTON_B) { // Desliga o alarme depois que foi disparado
        if (current_time - last_press_time_B > DEBOUNCE_TIME * 1000) { // Debounce
            last_press_time_B = current_time;  // Atualiza o tempo da última pressão
            if (alarm_triggered) {
                alarm_triggered = false; // Desativa o alarme
                update_display();
            }
        }
    }
}

int main() {
    stdio_init_all();
    init_gpio();
    pwm_setup();

    // Inicializa a estrutura do display
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, SSD1306_ADDR, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd); // Configura o display
    ssd1306_send_data(&ssd); // Envia os dados para o display

    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
    update_display();

     // Inicializa o PIO (ws2812_program)
     uint offset = pio_add_program(pio, &ws2812_program);
     sm = pio_claim_unused_sm(pio, true);
     ws2812_program_init(pio, sm, offset, MATRIX_PIN);

    // Configura as interrupções para os botões
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &button_irq_handler);

    while (true) {
        adc_select_input(2); // Seleciona o ADC para o microfone. O pino 28 como entrada analógica
        last_mic_value = adc_read(); // Lê o valor ADC no microfone
        printf("Microphone: %d\n", last_mic_value);

        if ((last_mic_value > MIC_LIMIT) && pwm_enabled) {
            play_siren();
        } else if (!alarm_triggered) {
            set_led_intensity(last_mic_value);
        }
        update_display(); // Atualiza a tela com cada leitura do microfone
        update_matrix_leds();
    }
}