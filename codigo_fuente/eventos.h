#ifndef EVENTOS_H
#define EVENTOS_H

typedef enum {
    VOID = 0,  // Reservado para inicializar la cola
    TIMER0,
    TIMER1,
		ALARMA_OVERFLOW,
		ev_BOTON_1,
		ev_BOTON_2,
		ALARMA_BOTONES,
		MODO_POWER_DOWN,
		ev_VISUALIZAR_CUENTA,
		ev_VISUALIZAR_HELLO,
		ev_LATIDO,
		ev_RX_SERIE,
		ev_TX_SERIE,
		ev_CONFIRMAR_JUGADA,
	
		// Pruebas del modulo alarmas software
		ALARMA_1,
		ALARMA_2,
		ALARMA_3,
		ALARMA_4,
		ALARMA_5,

} EVENTO_T;

#endif
