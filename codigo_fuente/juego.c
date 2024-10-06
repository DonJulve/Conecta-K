#include "juego.h"
TABLERO cuadricula;

//static uint32_t cuenta;
static uint32_t numero_eventos[6] = {0,0,0,0,0,0};
static uint8_t partida_iniciada;
static uint8_t turno;
static uint8_t cancelable;
static uint8_t continuable;
static uint8_t fila, columna, color;
static volatile uint8_t entrada[8] = {0, 0, 0, 0, 0, 0, 0, 0 };
static char buffer_pantalla[2000];
static char vista_previa[2000];
static char buffer_info[2500];
static uint32_t (*callback_1)();	// Funcion callback de FIFO_encolar
static GPIO_HAL_PIN_T pin_serie_error;
static GPIO_HAL_PIN_T numero_pines_serie_error;

static uint32_t intervalo_tiempo_procesador;
static uint32_t tiempo_humano;
static uint32_t tiempo_computo_conecta_K;
static uint32_t numero_partidas;
static uint32_t intervalo;
static uint32_t tiempo_excato;

void juego_inicializar(uint32_t (*funcion_callback_1)(), GPIO_HAL_PIN_T pin_s, GPIO_HAL_PIN_T numero_pines_s){
	//cuenta = 0;
	intervalo_tiempo_procesador = 0;
	partida_iniciada = 0;
	turno = 1;
	cancelable = 0;
	continuable = 1;
	numero_partidas = 0;
	tiempo_computo_conecta_K = 0;
	tiempo_humano = 0;
	
	pin_serie_error = pin_s;
	numero_pines_serie_error = numero_pines_s;
	gpio_hal_sentido(pin_s, numero_pines_s, GPIO_HAL_PIN_DIR_OUTPUT);
	tablero_inicializar(&cuadricula);
	conecta_K_test_cargar_tablero(&cuadricula, tablero_test);
	callback_1 = funcion_callback_1;
	
	visualizar_informacion_inicio();
}


void juego_tratar_evento(EVENTO_T ID_evento, uint32_t auxData){
	if (ID_evento == ev_RX_SERIE && continuable == 1){
	char buffer_comandos[3] = {'N','E','W'};
	uint32_t comando;
	comando = (buffer_comandos[0] << 16) | (buffer_comandos[1] << 8) | (buffer_comandos[2]);

	if(auxData == comando && partida_iniciada == 0){
		inicializar_partida();
		return;
	}
	if (partida_iniciada == 1){
			buffer_comandos[0] = 'E';
			buffer_comandos[1] = 'N';
			buffer_comandos[2] = 'D';
			comando = (buffer_comandos[0] << 16) | (buffer_comandos[1] << 8) | (buffer_comandos[2]);
			tiempo_humano = tiempo_humano + (clock_getus() - intervalo);
		if (auxData == comando){
			gpio_hal_escribir(pin_serie_error, numero_pines_serie_error, 0);
			mostrar_estadisticas(END);
			return;
		}
		else{
			uint8_t guion = (uint8_t)((auxData >> 8) & 0xFF);
			
			if (guion == '-'){
				entrada[1] = (uint8_t)((auxData >> 16) & 0xFF) - '0';
				entrada[2] = (uint8_t)(auxData & 0xFF) - '0';
				entrada[3] = turno;
	
				entrada_leer(entrada, &fila, &columna, &color);
				if(tablero_fila_valida(fila) && tablero_columna_valida(columna) && tablero_color_valido(color)){
					if (celda_vacia(tablero_leer_celda(&cuadricula, fila, columna))){
						continuable = 0;
						tiempo_excato = clock_getus();
						conecta_K_previsualizar_tablero(&cuadricula, vista_previa, fila, columna);
						tiempo_excato = clock_getus();
						tiempo_computo_conecta_K = tiempo_computo_conecta_K + tiempo_excato;
						linea_serie_drv_enviar_array(vista_previa);
						cancelable = 1;
						alarma_activar(ev_CONFIRMAR_JUGADA, 3000, 0);
						gpio_hal_escribir(pin_serie_error, numero_pines_serie_error, 0);
						return;
					}
				}
				continuable = 0;
				strcpy(buffer_pantalla, "\nCasilla invalida \n");
				linea_serie_drv_enviar_array(buffer_pantalla);
				gpio_hal_escribir(pin_serie_error, numero_pines_serie_error, 1);
				return;
			}
		}
	}
	continuable = 0;
	strcpy(buffer_pantalla, "\nComando incorrecto \n");
	linea_serie_drv_enviar_array(buffer_pantalla);
	gpio_hal_escribir(pin_serie_error, numero_pines_serie_error, 1);
}
	else if (ID_evento == ev_CONFIRMAR_JUGADA && partida_iniciada == 1 && continuable == 1){
		tiempo_humano += 3000;
		tiempo_excato = clock_getus();
		if(tablero_insertar_color(&cuadricula, fila, columna, color) == EXITO){
			continuable = 0;
			conecta_K_visualizar_tablero_final(&cuadricula, buffer_pantalla);
			linea_serie_drv_enviar_array(buffer_pantalla);
			cancelable = 0;
							
			if(conecta_K_hay_linea_arm_arm_op(&cuadricula, fila, columna, color)){
					mostrar_estadisticas(VICTORIA);
			}
			else{
				//El juego sigue
				//Cambio de color
				turno = (turno % 2) + 1;
				entrada[0] ++;
			}
		}
		tiempo_computo_conecta_K = tiempo_computo_conecta_K + (clock_getus() - tiempo_excato);
	}
	else if (ID_evento == ev_BOTON_1 && cancelable == 1 && partida_iniciada == 1 && continuable == 1){
		if (auxData == 1){
			return;
		}
		alarma_activar(ev_CONFIRMAR_JUGADA, 0, 0);
		cancelable = 0;
		continuable = 0;
		tiempo_excato = clock_getus();
		conecta_K_visualizar_tablero_final(&cuadricula, buffer_pantalla);
		tiempo_computo_conecta_K = tiempo_computo_conecta_K + (clock_getus() - tiempo_excato);
		linea_serie_drv_enviar_array(buffer_pantalla);
	}
	else if (ID_evento == ev_BOTON_1 && partida_iniciada == 0){
			inicializar_partida();
	}
	else if (ID_evento == ev_BOTON_2  && continuable == 1){
		if (partida_iniciada == 0){
			inicializar_partida();
			return;
		}
		
		if (auxData == 1){
			return;
		}
		tiempo_humano = tiempo_humano + (clock_getus() - intervalo);
		mostrar_estadisticas(BOTON_RENDIRSE);
		//Sacar stats
	}
	else if (ID_evento == ev_TX_SERIE){
		continuable = 1;
		
	}
}


//Funcion de stats que recibira el activador que lo llame (END, boton 2, etc...) como parametro y entonces lo pondrá como causa de fin

void mostrar_estadisticas(CAUSA causa){
		partida_iniciada = 0;
		intervalo_tiempo_procesador = (clock_getus() - intervalo_tiempo_procesador);
		numero_eventos[0] = callback_1(VOID) - numero_eventos[0];
		numero_eventos[1] = callback_1(ev_RX_SERIE) - numero_eventos[1];
		numero_eventos[2] = callback_1(ev_CONFIRMAR_JUGADA) - numero_eventos[2];
		numero_eventos[3] = callback_1(ev_BOTON_1) - numero_eventos[3];
		numero_eventos[4] = callback_1(ev_BOTON_2) - numero_eventos[4];
		numero_eventos[5] = callback_1(ev_TX_SERIE) - numero_eventos[5];
		if(causa == END){
			sprintf(buffer_info,	"\nLa partida ha terminado porque el jugador %u ha ejecutado el comando END \n"
																"El tiempo total de procesador en esta partida es: %u ms \n"			// intervalo_tiempo_procesador
																"El tiempo total de computo de conecta_K_hay_linea es: %u us \n"		// tiempo_computo_conecta_K
																"El tiempo medio de computo de conecta_K_hay_linea es: %u us \n"		// tiempo_computo_conecta_K/numero_partidas
																"El numero de eventos totales encolados es: %u \n"									// numero_eventos[0]
																"El numero de eventos RX_SERIE encolados es: %u \n"									// numero_eventos[1]
																"El numero de eventos CONFIRMAR_JUGADA encolados es: %u \n"					// numero_eventos[2]
																"El numero de eventos BOTON_1 encolados es: %u \n"									// numero_eventos[3]
																"El numero de eventos BOTON_2 encolados es: %u \n"									// numero_eventos[4]
																"El numero de eventos TX_SERIE encolados es: %u \n"									// numero_eventos[5]
																"Para empezar una nueva partida introduzca el comando $NEW! o pulse un boton (el jugador que haya perdido sera el primero en comenzar) \n\n\n",
																turno, intervalo_tiempo_procesador, tiempo_computo_conecta_K, tiempo_computo_conecta_K/numero_partidas,
																numero_eventos[0], numero_eventos[1], numero_eventos[2], numero_eventos[3], numero_eventos[4], numero_eventos[5]);
		}
		else if(causa == VICTORIA){
			sprintf(buffer_info,			"%s"
																"\nLa partida ha terminado porque ha ganado el jugador %u \n"
																"El tiempo total de procesador en esta partida es: %u ms \n"			// intervalo_tiempo_procesador
																"El tiempo total de computo de conecta_K_hay_linea es: %u us \n"		// tiempo_computo_conecta_K
																"El tiempo medio de computo de conecta_K_hay_linea es: %u us \n"		// tiempo_computo_conecta_K/numero_partidas
																"El numero de eventos totales encolados es: %u \n"									// numero_eventos[0]
																"El numero de eventos RX_SERIE encolados es: %u \n"									// numero_eventos[1]
																"El numero de eventos CONFIRMAR_JUGADA encolados es: %u \n"					// numero_eventos[2]
																"El numero de eventos BOTON_1 encolados es: %u \n"									// numero_eventos[3]
																"El numero de eventos BOTON_2 encolados es: %u \n"									// numero_eventos[4]
																"El numero de eventos TX_SERIE encolados es: %u \n"									// numero_eventos[5]
																"Para empezar una nueva partida introduzca el comando $NEW! o pulse un boton (el jugador que haya perdido sera el primero en comenzar) \n\n\n",
																buffer_pantalla, turno, intervalo_tiempo_procesador, tiempo_computo_conecta_K, tiempo_computo_conecta_K/numero_partidas,
																numero_eventos[0], numero_eventos[1], numero_eventos[2], numero_eventos[3], numero_eventos[4], numero_eventos[5]);
			turno = (turno % 2) + 1;
		}
		else if(causa == BOTON_RENDIRSE){
			sprintf(buffer_info,	"\nLa partida ha terminado porque el jugador %d ha pulsado el boton de rendirse \n"
																"El tiempo total de procesador en esta partida es: %u ms \n"			// intervalo_tiempo_procesador
																"El tiempo total de computo de conecta_K_hay_linea es: %u us \n"		// tiempo_computo_conecta_K
																"El tiempo medio de computo de conecta_K_hay_linea es: %u us \n"		// tiempo_computo_conecta_K/numero_partidas
																"El numero de eventos totales encolados es: %u \n"									// numero_eventos[0]
																"El numero de eventos RX_SERIE encolados es: %u \n"									// numero_eventos[1]
																"El numero de eventos CONFIRMAR_JUGADA encolados es: %u \n"					// numero_eventos[2]
																"El numero de eventos BOTON_1 encolados es: %u \n"									// numero_eventos[3]
																"El numero de eventos BOTON_2 encolados es: %u \n"									// numero_eventos[4]
																"El numero de eventos TX_SERIE encolados es: %u \n"									// numero_eventos[5]
																"Para empezar una nueva partida introduzca el comando $NEW! o pulse un boton (el jugador que haya perdido sera el primero en comenzar) \n\n\n",
																turno, intervalo_tiempo_procesador, tiempo_computo_conecta_K, tiempo_computo_conecta_K/numero_partidas,
																numero_eventos[0], numero_eventos[1], numero_eventos[2], numero_eventos[3], numero_eventos[4], numero_eventos[5]);
		}
		
//		sprintf(buffer_pantalla,	"\nEl tiempo total de procesador en esta partida es: %u ms \n"			// intervalo_tiempo_procesador
//															"El tiempo total de computo de conecta_K_hay_linea es: %u us \n"	// tiempo_computo_conecta_K
//															"El tiempo medio de computo de conecta_K_hay_linea es: %u us \n"	// tiempo_computo_conecta_K/numero_partidas
//															"El numero de eventos totales encolados es: %u \n"								// numero_eventos[0]
//															"El numero de eventos RX_SERIE encolados es: %u \n"								// numero_eventos[1]
//															"El numero de eventos CONFIRMAR_JUGADA encolados es: %u \n"				// numero_eventos[2]
//															"El numero de eventos BOTON_1 encolados es: %u \n"								// numero_eventos[3]
//															"El numero de eventos BOTON_2 encolados es: %u \n"								// numero_eventos[4]
//															"El numero de eventos TX_SERIE encolados es: %u \n"								// numero_eventos[5]
//															"Para empezar una nueva partida introduzca el comando $NEW! (el jugador que haya perdido sera el primero en comenzar) \n\n\n",
//															intervalo_tiempo_procesador, tiempo_computo_conecta_K, tiempo_computo_conecta_K/numero_partidas,
//															numero_eventos[0], numero_eventos[1], numero_eventos[2], numero_eventos[3], numero_eventos[4], numero_eventos[5]);
																									
		linea_serie_drv_enviar_array(buffer_info);
		entrada[0] = 0;
}

void visualizar_informacion_inicio(void){
		sprintf(buffer_info, 	"\n*Conecta K*\n"
															"-Para empezar una nueva partida introduzca el comando $NEW! o pulse un boton\n"
															"-Para acabar una partida introduzca el comando $END!\n"
															"-Para hacer una jugada introduce el comando $#-#! donde el primer # es la fila y el segundo # es la columna\n"
															"-Para cancelar una jugada pulse el boton 1 antes de 3 segundos\n"
															"-Para rendirse pulse el boton 2\n"
															"-El primer jugador en hacer una linea de la longitud establecida gana (por defecto 4)\n"
															"-Para empezar una nueva partida debe haber acabado la anterior\n"
															"-Empieza el jugador %d\n\n", turno);
		linea_serie_drv_enviar_array(buffer_info);
}

void inicializar_partida(void){
		tablero_inicializar(&cuadricula);
		conecta_K_test_cargar_tablero(&cuadricula, tablero_test);
		entrada_inicializar(entrada);
		partida_iniciada = 1;
		
		
		conecta_K_visualizar_tablero_final(&cuadricula, buffer_pantalla);
		linea_serie_drv_enviar_array(buffer_pantalla);
		gpio_hal_escribir(pin_serie_error, numero_pines_serie_error, 0);
		numero_partidas++;
		tiempo_computo_conecta_K = 0;
		intervalo_tiempo_procesador = clock_getus();
		intervalo = clock_getus();
}
