#ifndef GESTOR_ALARMAS_H
#define GESTOR_ALARMAS_H

#include <LPC210x.H>
#include <inttypes.h>
#include "eventos.h"
#include "gpio_hal.h"

#define ALARMAS_MAX 4

static uint8_t num_activas;

typedef struct {
	uint8_t periodica;
	EVENTO_T ID_evento;
	uint32_t auxData;
	uint32_t periodo;	
	uint8_t activa;			// si es 0 no esta activada
}Alarma;

void alarma_inicializar(GPIO_HAL_PIN_T pin_overflow, void (*funcion_callback_1)());		// callback_1 -> FIFO_encolar
void alarma_activar(EVENTO_T ID_evento, uint32_t retardo, uint32_t auxData);
void comprobar_alarmas(unsigned int tiempo);
void desactivar_alarma(EVENTO_T ID_evento);
void alarma_overflow(void);
void alarma_tratar_evento(unsigned int tiempo);
	
#endif
