#ifndef LINEA_SERIE_HAL_H
#define LINEA_SERIE_HAL_H

#include <LPC210X.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eventos.h"

#define MAX_BUFFER_SIZE 4

void linea_serie_hal_init(void (*funcion_callback_enviar)(char), void (*funcion_callback_encolar)());
char linea_serie_hal_recibir_char(void);
void linea_serie_hal_escribir_char(char c);

void linea_serie_hal_enviar_array(char comando[]);
void linea_serie_hal_continuar_envio(void);



#endif
