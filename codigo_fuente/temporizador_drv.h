
#ifndef DRIVER_H
#define DRIVER_H

#include <inttypes.h>
#include "temporizador_hal.h"
#include "eventos.h"

// Función que programa un contador para que pueda ser utilizado
void temporizador_drv_iniciar(void);
	
// Función que inicia la cuenta de un contador de forma indefinida. 
void temporizador_drv_empezar(void);

// Función que lee el tiempo que lleva contando el contador desde 
// la última vez que se ejecutó temporizador_drv_empezar y lo 
// devuelve en microsegundos. 
uint64_t temporizador_drv_leer(void);

// Detiene el contador y devuelve el tiempo transcurrido 
// desde el último temporizador_drv_empezar
uint64_t temporizador_drv_parar(void);

void temporizador_drv_reloj (uint32_t periodo, void 
(*funcion_encolar_evento)(), EVENTO_T ID_evento);
	
void funcion_callback_temporizador(uint32_t a);

uint64_t __swi(0) clock_getus(void);
#endif // DRIVER_H
