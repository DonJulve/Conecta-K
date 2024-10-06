#include "gpio_hal.h"


void gpio_hal_iniciar(void) {
		PINSEL0 = 0x00000000;
    PINSEL1 = 0x00000000;
}

void gpio_hal_sentido(GPIO_HAL_PIN_T gpio_inicial, uint8_t num_bits, gpio_hal_pin_dir_t direccion) {
		int i;
    // Comprueba que el número de bits especificado sea válido
    if (num_bits <= 0 || num_bits > 32) {
        while(1);
    }
    // Configura pines como entrada o salida según la dirección
    if (direccion == GPIO_HAL_PIN_DIR_OUTPUT) {
        for (i = 0; i < num_bits; i++) {
            IODIR |= (1 << (gpio_inicial + i)); // Configura como salida
        }
    } 
		else {
        for (i = 0; i < num_bits; i++) {
            IODIR &= ~(1 << (gpio_inicial + i)); // Configura como entrada
        }
    }
}

uint32_t gpio_hal_leer(GPIO_HAL_PIN_T gpio_inicial, uint8_t num_bits){
	uint32_t valor_leido = 0;
	int i;
	for (i = 0; i < num_bits; i++) {
        valor_leido |= ((IOPIN >> (gpio_inicial + i)) & 0x01) << i;
    }
    return valor_leido;
}


void gpio_hal_escribir(GPIO_HAL_PIN_T bit_inicial, uint8_t num_bits, uint32_t valor) {
		int i = 0;
    // Máscara para obtener los num_bits menos significativos del valor
    uint32_t mascara = (1u << num_bits) - 1;
    // Aplica la máscara para obtener los num_bits menos significativos de valor
    uint32_t valor_escrito = valor & mascara;
    // Desplaza los bits escritos a la posición deseada
		for (i = 0; i < num_bits; i++){
			IOCLR = 1 << i << bit_inicial;
		}
    valor_escrito <<= bit_inicial;
		IOSET = valor_escrito;
}
