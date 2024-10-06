
#include "temporizador_drv.h"

static void (*FIFO_encolar)();
static EVENTO_T evento;

void temporizador_drv_iniciar(void){
	temporizador_hal_iniciar();
}

void temporizador_drv_empezar(void){
	temporizador_hal_empezar();
}

uint64_t temporizador_drv_leer(void){
	return temporizador_hal_leer() * temporizador_hal_ticks2us;
}

uint64_t temporizador_drv_parar(void){
	return temporizador_hal_parar() * temporizador_hal_ticks2us;
}

// Funcion para crear una alarma.
void temporizador_drv_reloj (uint32_t periodo, void 
(*funcion_encolar_evento)(), EVENTO_T ID_evento){
	FIFO_encolar = funcion_encolar_evento;
	evento = ID_evento;
	temporizador_hal_reloj (periodo, funcion_callback_temporizador);
}

void funcion_callback_temporizador(uint32_t tiempo) {
	FIFO_encolar(evento, tiempo);
}

uint64_t __swi(0) clock_getus(void);
uint64_t __SWI_0 (void) {
	return temporizador_hal_leer() / temporizador_hal_ticks2us;
}
