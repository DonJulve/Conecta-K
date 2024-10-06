#include "planificador.h"

void planificador(){
	ElementoCola evento;
	uint8_t alarma_power_down_activa = 0;
	uint8_t pwdown = 0;
	gpio_hal_iniciar();
	FIFO_inicializar(GPIO_OVERFLOW, GPIO_OVERFLOW_BITS);
	alarma_inicializar(GPIO_OVERFLOW, &FIFO_encolar);
	temporizador_drv_reloj(1, &FIFO_encolar, 	TIMER1);
	temporizador_drv_iniciar();
	temporizador_drv_empezar();
	inicializar_botones(&FIFO_encolar, ev_BOTON_1);	// Para probar alarmas comentar esto
	juego_inicializar(&FIFO_estadisticas, COMANDO_ERRONEO, COMANDO_ERRONEO_BITS);
	inicializar_visualizar(GPIO_VISUALIZAR, GPIO_VISUALIZAR_BITS, GPIO_HELLO_WORLD, GPIO_HELLO_WORLD_BITS);
	linea_serie_drv_inicializar(GPIO_SERIE_ERROR, GPIO_SERIE_ERROR_BITS, &FIFO_encolar, ev_RX_SERIE);
	WDT_hal_inicializar(1);
	
	
	// Prueba de hellow_world_parte_A
	//hello_world_inicializar_parte_b(GPIO_HELLO_WORLD, GPIO_HELLO_WORLD_BITS);
	//temporizador_drv_reloj(10, FIFO_encolar, 	TIMER1);
	
	// Prueba alarmas software
	//prueba_alarma_software();
	
	// Prieba de hello_world_partaB
	 hello_world_inicializar_parte_b(GPIO_HELLO_WORLD, GPIO_HELLO_WORLD_BITS, &FIFO_encolar);
	
	//
	while(1){
		WDT_hal_feed();
		if (FIFO_extraer(&evento.ID_evento,&evento.auxData) != 0){
			switch (evento.ID_evento) {
				case TIMER1:									// Evento de tipo timer1
					//hello_world_tick_tack();	// Prueba de hello world
					alarma_tratar_evento(evento.auxData);		// Alarmas software
				break;
				case ALARMA_OVERFLOW:
					alarma_overflow();
				break;
				case ALARMA_BOTONES:
					comprobar_botones();
				break;
				case ev_BOTON_1:
					reiniciar_alarma_power_down(&alarma_power_down_activa);
					juego_tratar_evento(ev_BOTON_1, pwdown);
					pwdown = 0;
				break;
				case ev_BOTON_2:
					reiniciar_alarma_power_down(&alarma_power_down_activa);
					juego_tratar_evento(ev_BOTON_2, pwdown);
					pwdown = 0;
				break;
				case MODO_POWER_DOWN:
					alarma_power_down_activa = 0;		// permite volver a llamar a la alarma
					power_hal_deep_sleep();
					pwdown = 1;
				break;
				case ev_VISUALIZAR_CUENTA:
					visualizar_cuenta(evento.auxData);
				break;
				case ev_VISUALIZAR_HELLO:
					visualizar_hello_world(evento.auxData);
				break;
				case ev_LATIDO:
					hello_world_tratar_evento();
				break;
				case ev_RX_SERIE:
					reiniciar_alarma_power_down(&alarma_power_down_activa);
					juego_tratar_evento(ev_RX_SERIE, evento.auxData);
				break;
				case ev_TX_SERIE:
					juego_tratar_evento(ev_TX_SERIE, evento.auxData);
				break;
				case ev_CONFIRMAR_JUGADA:
					juego_tratar_evento(ev_CONFIRMAR_JUGADA, evento.auxData);
				break;
				
				
//				// Pruebas del modulo de alarmas software
//				case ALARMA_1:
//					alarma_1();
//				break;
//				case ALARMA_2:
//					alarma_2();
//				break;
//				case ALARMA_3:
//					alarma_3();
//				break;
//				case ALARMA_4:
//					alarma_4();
//				break;
//				case ALARMA_5:
//					alarma_5();
//				break;
		
			}
		}
		else {
			if (alarma_power_down_activa == 0){
				alarma_activar(MODO_POWER_DOWN, USUARIO_AUSENTE, 0);	// activa alarma para power_down
				alarma_power_down_activa = 1;
			}
			power_hal_wait();								// Modo idle
		}
	}
}

void desactivar_alarma_power_down(uint8_t *alarma_power_down_activa){
		*alarma_power_down_activa = 0;
		alarma_activar(MODO_POWER_DOWN, 0, 0);		// desactiva la alarma
}

void reiniciar_alarma_power_down(uint8_t *alarma_power_down_activa){
	desactivar_alarma_power_down(alarma_power_down_activa);
	alarma_activar(MODO_POWER_DOWN, USUARIO_AUSENTE, 0);	// activa alarma para power_down
	*alarma_power_down_activa = 1;
}
