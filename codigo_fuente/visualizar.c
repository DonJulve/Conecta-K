#include "visualizar.h"
#include <LPC210x.H>

static GPIO_HAL_PIN_T pin_visualizar;
static GPIO_HAL_PIN_T numero_pines_visualizar;

static GPIO_HAL_PIN_T pin_hello_world;
static GPIO_HAL_PIN_T numero_pines_hello_world;

void inicializar_visualizar(GPIO_HAL_PIN_T pin_v, GPIO_HAL_PIN_T numero_pines_v, GPIO_HAL_PIN_T pin_w, GPIO_HAL_PIN_T numero_pines_w){
	pin_visualizar = pin_v;
	numero_pines_visualizar = numero_pines_v;
	pin_hello_world = pin_w;
	numero_pines_hello_world = numero_pines_w;
	gpio_hal_sentido(pin_visualizar, numero_pines_visualizar, GPIO_HAL_PIN_DIR_OUTPUT);
}

void visualizar_cuenta(uint32_t cuenta) {
	gpio_hal_escribir(pin_visualizar, numero_pines_visualizar, cuenta);
}

void visualizar_hello_world(uint32_t cuenta){
	gpio_hal_escribir(pin_hello_world, numero_pines_hello_world, cuenta);
}
