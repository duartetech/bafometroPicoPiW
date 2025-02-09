#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "inc/ssd1306.h"  
#include <string.h>
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define LED_VERDE_PIN 11
#define LED_AZUL_PIN 12
#define LED_VERMELHO_PIN 13
#define I2C_SDA 14
#define I2C_SCL 15
#define ADC_GPIO_PIN 28
#define ADC_CHANNEL 2
#define BUZZER_PIN 21
#define BUZZER_FREQUENCY 10000

// Função para controlar os LEDs com base no valor do ADC
void controlar_leds(int adc_percent) {
    if (adc_percent <30) {
        gpio_put(LED_VERDE_PIN, 1);
        gpio_put(LED_AZUL_PIN, 0);
        gpio_put(LED_VERMELHO_PIN, 0);
    } else if (adc_percent > 30 && adc_percent < 70) {
        gpio_put(LED_VERDE_PIN, 0);
        gpio_put(LED_AZUL_PIN, 1);
        gpio_put(LED_VERMELHO_PIN, 0);
    } else {
        gpio_put(LED_VERDE_PIN, 0);
        gpio_put(LED_AZUL_PIN, 0);
        gpio_put(LED_VERMELHO_PIN, 1);
    }
}
// Função para inicializar o PWM no pino do buzzer
void pwm_init_buzzer(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (BUZZER_FREQUENCY * 4096));
    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(pin, 0);
}

// Acionar o beep quando o nível de álcool estiver alto
void alerta_buzzer(uint pin, int adc_percent) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    if (adc_percent > 70) {
        pwm_set_gpio_level(pin, 2048);
    } else {
        pwm_set_gpio_level(pin, 0);  
    }
}

// Exibe o nível de álcool no display
void exibir_nivel_alcool(int adc_percent, uint8_t *ssd, struct render_area *frame_area) {
    
    char adc_text[16];
    snprintf(adc_text, sizeof(adc_text), " %d%%", adc_percent);

    char *text[] = {
        "NIVEL DE ALCOOL",
        adc_text
    };

    memset(ssd, 0, ssd1306_buffer_length);

    int y = 0;
    for (uint i = 0; i < (sizeof(text) / sizeof(text[0])); i++) {
        ssd1306_draw_string(ssd, 5, y, text[i]);
        y += 8;
    }

    render_on_display(ssd, frame_area);
}

// Exibe a contagem regressiva enquanto o sensor de alcool esquenta
void esquentando_sensor(uint8_t *ssd, struct render_area *frame_area) {
    char texto[4];
    memset(ssd, 0, ssd1306_buffer_length);

    ssd1306_draw_string(ssd, 5, 0, "Esquentando");
    ssd1306_draw_string(ssd, 5, 12, "Sensor");
    
// Uma espera de 3 minutos (180 segundos) para esquentar o sensor e ler dados mais precisos
    for (int i = 180; i >= 0; i--) {
        snprintf(texto, sizeof(texto), "%d", i);
        memset(ssd + (128 * 2) + 20, 0, 60);
        ssd1306_draw_string(ssd, 50, 20, texto);
        render_on_display(ssd, frame_area);
        sleep_ms(1000);
    }
}

int main() {
    stdio_init_all();

    adc_init();
    adc_gpio_init(ADC_GPIO_PIN);
    adc_select_input(ADC_CHANNEL);

    gpio_init(LED_VERDE_PIN);
    gpio_set_dir(LED_VERDE_PIN, GPIO_OUT);
    
    gpio_init(LED_AZUL_PIN);
    gpio_set_dir(LED_AZUL_PIN, GPIO_OUT);
    
    gpio_init(LED_VERMELHO_PIN);
    gpio_set_dir(LED_VERMELHO_PIN, GPIO_OUT);

    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    ssd1306_init();

    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);

    struct render_area frame_area = {
        .start_column = 0,
        .end_column = ssd1306_width - 1,
        .start_page = 0,
        .end_page = ssd1306_n_pages - 1
    };

    calculate_render_area_buffer_length(&frame_area);
    render_on_display(ssd, &frame_area);

    gpio_init(9);
    gpio_set_dir(9, GPIO_IN);

    esquentando_sensor(ssd, &frame_area);
    pwm_init_buzzer(BUZZER_PIN);

    while (true) {
        uint16_t adc_value = adc_read();
        // Converte os valores do ADC em uma porcentagem de 0 a 100
        // Nos meus testes eu só consegui chegar em média em valores 2200
        // Então resolvi definir esse como valor maximo para teste no sensor real MQ-3
        int adc_percent = (adc_value * 100) / 2200;

        controlar_leds(adc_percent);
        exibir_nivel_alcool(adc_percent, ssd, &frame_area);
        alerta_buzzer(BUZZER_PIN, adc_percent); 
        
        sleep_ms(500);
    }

    return 0;
}
