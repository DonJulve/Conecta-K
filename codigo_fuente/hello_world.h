#ifndef HELLO_WORLD
#define HELLO_WORLD

#include "eventos.h"
#include "Gestor_alarmas.h"
#include <inttypes.h>

// Funciones parte a
void hello_world_inicializar_parte_a(GPIO_HAL_PIN_T hello_world, GPIO_HAL_PIN_T bits,  void (*funcion_callback_1)()); 	// callback_1 -> FIFO_encolar
void hello_world_tick_tack(void);

// Funciones parte B
void hello_world_inicializar_parte_b(GPIO_HAL_PIN_T hello_world, GPIO_HAL_PIN_T bits,  void (*funcion_callback_1)());		// callback_1 -> FIFO_encolar
void hello_world_tratar_evento(void);
void hello_world_visualizar(uint32_t cuenta);

#endif
