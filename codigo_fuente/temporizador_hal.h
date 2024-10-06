
#ifndef HAL_H
#define HAL_H

#include <inttypes.h>
#include "LPC210X.H"
#include "eventos.h"

enum {
	temporizador_hal_ticks2us = 1,
};

// Función que programa un contador para que pueda ser utilizado.
void temporizador_hal_iniciar(void);

// Función que inicia la cuenta de un contador de forma indefinida
void  temporizador_hal_empezar(void);

// función que lee el tiempo que lleva contando  el contador desde 
//la última vez que se ejecutó temporizador_hal_empezar y lo devuelve 
// en ticks
uint64_t temporizador_hal_leer(void);

// Detiene el contador y devuelve el tiempo en ticks transcurrido 
// desde el último temporizador_hal_empezar
uint64_t temporizador_hal_parar(void);

// Tratamiento de la interrupcion del timer0
void RSI_timer0 (void) __irq;

// Tratamiento de la interrupcion del timer1
void RSI_timer1 (void) __irq;

// Funcion que inicializa el timer 1 como alarma
void temporizador_hal_reloj (uint32_t periodo, 
	void (*funcion_callback)());

#endif // HAL_H
