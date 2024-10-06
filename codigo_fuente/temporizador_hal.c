#include "temporizador_hal.h"

static unsigned int timer0_count;
static unsigned int timer1_count;

static void (*funcion_rsi)();

// Tratamiento de interrupcion de timer0
void RSI_timer0 (void) __irq {
    timer0_count++;
    T0IR = 1;                              // Bajamos la interrupcion del timer
    VICVectAddr = 0;                       // Bajamos la interrupci�n
}

 
// Tratamiento de interrupcion de timer1
void RSI_timer1 (void) __irq {
    timer1_count++;
    T1IR = 1;                              // Bajamos la interrupcion del timer
		funcion_rsi(timer1_count);
    VICVectAddr = 0;                       // Bajamos la interrupci�n
}


void temporizador_hal_iniciar(void){
	// configuration of Timer 0
	T0PR = 14;													// 1us
	T0MR0 = 1000;                       // Interrumpe cada 1ms = 1000us
	//T0MR0 = 10;                       // Interrumpe cada 10us
  T0MCR = 3;                   	  
  
	VICVectAddr0 = (unsigned long)RSI_timer0;          // introduce en el vector de interrupciones
	VICVectCntl0 = 0x20 | 4;  		

}


void  temporizador_hal_empezar(void){
	T0TCR = 1;                           						// activar timer0_count
	VICIntEnable = VICIntEnable | 0x00000010;       // Activar interrupciones timer0_count
	timer0_count = 0;
}


uint64_t temporizador_hal_leer(void){
	return timer0_count; /* T0MR0;	*/									// Cada vez que se incrementa tiimer0_count son 1000 ticks
}


uint64_t temporizador_hal_parar(void){
	T0TCR = 0;																									// Desactivar timer0
	VICIntEnable = VICIntEnable & ~0x00000010;                  // Desactivar timer0
	return temporizador_hal_leer();
}


// Funcion que inicializa el timer 1 como alarma
void temporizador_hal_reloj (uint32_t periodo, 
	void (*funcion_callback)()){
		
		if (periodo == 0){
			// Parar timer
			T1TCR = 0;
			VICIntEnable = VICIntEnable & ~0x00000020;
		}
		
		if ( periodo != 0){
			
			// Inicializar el timer 1
			T1MR0 = (15000 * periodo) - 1;                        // 1ms = 15000 tics
			T1MCR = 3;                   	  
			T1TCR = 1;

			VICVectAddr5 = (unsigned long)RSI_timer1;
			VICVectCntl5 = 0x20 | 5;

			funcion_rsi = funcion_callback;
			// Activar timer1 y resetear
			VICIntEnable = VICIntEnable | 0x00000020;
			timer1_count = 0;		
		}
}

