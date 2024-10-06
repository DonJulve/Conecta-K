#ifndef JUEGO_H
#define JUEGO_H

#include <LPC210x.H>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eventos.h"
#include "linea_serie_drv.h"
#include "temporizador_drv.h"
#include "Gestor_alarmas.h"
#include "WDT_hal.h"

#include "conecta_K_2023.h"
#include "tablero_test.h"
#include "entrada.h"
typedef enum {
    END = 0,
		VICTORIA,
		BOTON_RENDIRSE

} CAUSA;

void juego_inicializar(uint32_t (*funcion_callback_1)(), GPIO_HAL_PIN_T pin_s, GPIO_HAL_PIN_T numero_pines_s);		// callback_1 -> FIFO_encolar
void juego_tratar_evento(EVENTO_T ID_evento, uint32_t auxData);
void mostrar_estadisticas(CAUSA causa);
void visualizar_informacion_inicio(void);
void inicializar_partida(void);

#endif
