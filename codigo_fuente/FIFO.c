#include "FIFO.h"

static ElementoCola cola[CAPACIDAD_COLA];
static int inicio = 0;                
static int final = 0; 
static uint32_t contador_general;
static uint32_t contador[NUM_EVENTOS];
static GPIO_HAL_PIN_T overflow_pin;	
static GPIO_HAL_PIN_T numero_overflow_pin;

void FIFO_inicializar(GPIO_HAL_PIN_T pin_overflow, GPIO_HAL_PIN_T numero_pin) {
    overflow_pin = pin_overflow;
		numero_overflow_pin = numero_pin;
		gpio_hal_sentido(pin_overflow, numero_overflow_pin, GPIO_HAL_PIN_DIR_OUTPUT);
		contador_general = 0;
}

void FIFO_encolar(EVENTO_T ID_evento, uint32_t auxData) {
	
	// COMPROBAR INTERRUPCIONES ACTIVAS
	uint8_t state_irq_bit;

		state_irq_bit = read_IRQ_bit();
		if (state_irq_bit == 0) {
			disable_irq();
		}
		
	// DESACTIVADAS -> DESACTIVAR
    if ((inicio + 1) % (CAPACIDAD_COLA + 1) == final) {
        gpio_hal_escribir(overflow_pin, 1, 1);
        while(1);
    }
		cola[inicio].ID_evento = ID_evento;
    cola[inicio].auxData = auxData;
		
		contador_general++;
		contador[ID_evento - 1] ++;

    // Actualiza el índice de entrada
    inicio = (inicio + 1) % (CAPACIDAD_COLA + 1);
		
		/*
		// Recuperamos el estado de la flag I
		// Si estaban activadas antes de entrar las volvemos a activar
		if ( bit_IRQ == 0) {	// ACTIVAS -> DESACTIVAR
		// LUEGO VOLVER A ACTIVAR
			enable_irq();
		}
		*/
		
		/*
		if (state_irq_bit == 0){
			enable_irq();
		}
		*/
		
		
}

uint8_t FIFO_extraer(EVENTO_T *ID_evento, uint32_t *auxData) {
		uint8_t retorno;
		uint8_t state_irq_bit;
	
		state_irq_bit = read_IRQ_bit();
		if (state_irq_bit == 0)
			disable_irq();
	
    if (inicio == final) {
				retorno = 0;  // La cola está vacía, no se ha devuelto ningún evento
    }
		else {
			// Extrae el evento más antiguo sin procesar
			*ID_evento = cola[final].ID_evento;
			*auxData = cola[final].auxData;
			// Actualiza el índice de salida
			final = (final + 1) % (CAPACIDAD_COLA + 1);
			retorno = 1;
		}
    
		/*
		// Recuperamos el estado de la flag I
		// Si estaban activadas antes de entrar las volvemos a activar
		if ( bit_IRQ == 0) {
		// LUEGO VOLVER A ACTIVAR
			enable_irq();
		}
		*/
		/*
		if (state_irq_bit == 0)
			enable_irq();
		*/
		
		
		return retorno; // Devuelve un valor distinto de cero para indicar que se ha extraído un evento
}

uint32_t FIFO_estadisticas(EVENTO_T ID_evento) {

    if (ID_evento == VOID) {
        return contador_general;
    } 
		else {
        return contador[ID_evento - 1];
    }
}
