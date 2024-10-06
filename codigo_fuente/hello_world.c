#include "hello_world.h"

static GPIO_HAL_PIN_T pin_inicio;
static GPIO_HAL_PIN_T numero_bits;
static void (*callback_1)();	// Funcion callback de FIFO_encoalar

// Funciones parte a
void hello_world_inicializar_parte_a(GPIO_HAL_PIN_T hello_world, GPIO_HAL_PIN_T bits,  void (*funcion_callback_1)()){
	gpio_hal_iniciar();
	gpio_hal_sentido(hello_world, bits, GPIO_HAL_PIN_DIR_OUTPUT);
	pin_inicio = hello_world;
	numero_bits = bits;
	callback_1 = funcion_callback_1;
}

void hello_world_tick_tack(){
	static uint8_t contador;
	gpio_hal_escribir(pin_inicio,numero_bits,contador);
	contador++;
}


// Funciones parte B
void hello_world_inicializar_parte_b(GPIO_HAL_PIN_T hello_world, GPIO_HAL_PIN_T bits,  void (*funcion_callback_1)()){
	pin_inicio = hello_world;
	numero_bits = bits;
	gpio_hal_sentido(hello_world, bits, GPIO_HAL_PIN_DIR_OUTPUT);
	alarma_activar(ev_LATIDO, 0x8000000A ,0);
	callback_1 = funcion_callback_1;
}

void hello_world_tratar_evento(void){
	static uint16_t hello_world_counter;
	callback_1(ev_VISUALIZAR_HELLO, hello_world_counter);
	hello_world_counter++;
}

