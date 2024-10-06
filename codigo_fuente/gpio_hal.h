#ifndef GPIO_LPC2105_H
#define GPIO_LPC2105_H

#include <inttypes.h>
#include <LPC210X.H>

typedef enum {
    GPIO_HAL_PIN_DIR_INPUT = 0,
    GPIO_HAL_PIN_DIR_OUTPUT = 1
} gpio_hal_pin_dir_t;


typedef uint32_t GPIO_HAL_PIN_T;


void gpio_hal_iniciar(void);
void gpio_hal_sentido(GPIO_HAL_PIN_T gpio_inicial, uint8_t num_bits, gpio_hal_pin_dir_t direccion);
uint32_t gpio_hal_leer(GPIO_HAL_PIN_T gpio_inicial, uint8_t num_bits);
void gpio_hal_escribir(GPIO_HAL_PIN_T bit_inicial, uint8_t num_bits, uint32_t valor);

#endif
	
