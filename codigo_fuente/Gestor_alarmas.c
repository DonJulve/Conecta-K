#include "Gestor_alarmas.h"

static Alarma lista_alarmas[ALARMAS_MAX];
static void (*FIFO_encolar)();	// Funcion callback de FIFO_encolar
static GPIO_HAL_PIN_T overflow;

void alarma_inicializar(GPIO_HAL_PIN_T pin_overflow, void (*funcion_callback_1)()){
	uint8_t i;
	num_activas = 0;
	for (i = 0; i < ALARMAS_MAX; i++){
		lista_alarmas[i].activa = 0;
	}
	FIFO_encolar = funcion_callback_1;
	overflow = pin_overflow;
}

void alarma_activar(EVENTO_T ID_evento, uint32_t retardo, uint32_t auxData){
	
	uint32_t mascara = 0x80000000;
	Alarma nueva_alarma;
	uint8_t i, activada;
	
	if (retardo == 0){	// Eliminar alarma
		desactivar_alarma(ID_evento);
	}
	else if (num_activas >= ALARMAS_MAX) {	// Desbordamiento de alarmas
		FIFO_encolar(ALARMA_OVERFLOW, 0);
	}
	else {	// Activar alarma
		nueva_alarma.ID_evento = ID_evento;
		nueva_alarma.auxData = auxData;
		nueva_alarma.activa = 1;
	
		// Comprobamos si es periodica
		if ((retardo & mascara) == mascara){
			nueva_alarma.periodica = 1;
			nueva_alarma.periodo = retardo ^ mascara;
		}
		else {
			nueva_alarma.periodica = 0;
			nueva_alarma.periodo = retardo;
		}
		
		// Añadimos a la nueva alarma a la lista de alarmas
		i = 0;
		activada = 0;
		while ( i < ALARMAS_MAX && activada == 0) {
			if (lista_alarmas[i].activa == 0){
				lista_alarmas[i] = nueva_alarma;
				num_activas++;
				activada = 1;
			}
			i++;
		}
	}
}

void comprobar_alarmas(unsigned int tiempo){
	uint8_t i,esPeriodica, estaActiva;
	uint32_t retardo = tiempo;
	for (i = 0; i < ALARMAS_MAX; i++){
		estaActiva = lista_alarmas[i].activa;
		esPeriodica = lista_alarmas[i].periodica;
		retardo = lista_alarmas[i].periodo;
		if (estaActiva && ((tiempo % retardo) == 0)){
			FIFO_encolar(lista_alarmas[i].ID_evento, 0);
			lista_alarmas[i].periodo = retardo;
			if (esPeriodica == 0){
				lista_alarmas[i].activa = 0;
				num_activas--;
			}
		}
	}
}

void desactivar_alarma(EVENTO_T ID_evento){
	uint8_t i = 0, encontrado = 0;
	while (i < ALARMAS_MAX && encontrado == 0){
		if (lista_alarmas[i].ID_evento == ID_evento){
				lista_alarmas[i].activa = 0;
				num_activas--;
				encontrado = 1;
		}
		i++;
	}
}

void alarma_overflow(void){
	gpio_hal_escribir(overflow, 1, 1);
	while(1);
}

void alarma_tratar_evento(unsigned int tiempo){
	comprobar_alarmas(tiempo);
}
