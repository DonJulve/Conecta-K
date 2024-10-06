#ifndef FIFO_H
#define FIFO_H

#include <inttypes.h>
#include "gpio_hal.h"
#include "eventos.h"
#include "llamadas_sistema.h"

#define CAPACIDAD_COLA 32
#define NUM_EVENTOS 19

typedef struct {
    EVENTO_T ID_evento;
    uint32_t auxData;
} ElementoCola;

void FIFO_inicializar(GPIO_HAL_PIN_T pin_overflow, GPIO_HAL_PIN_T numero_pin);

void FIFO_encolar(EVENTO_T ID_evento, uint32_t auxData);

uint8_t FIFO_extraer(EVENTO_T *ID_evento, uint32_t *auxData);

uint32_t FIFO_estadisticas(EVENTO_T ID_evento);

#endif
	
