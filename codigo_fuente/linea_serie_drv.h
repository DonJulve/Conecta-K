#ifndef LINEA_SERIE_DRV_H
#define LINEA_SERIE_DRV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linea_serie_hal.h"
#include "eventos.h"
#include "gpio_hal.h"

#define buffer_size 3

void linea_serie_drv_inicializar(GPIO_HAL_PIN_T pin_s, GPIO_HAL_PIN_T numero_pines_s, void (*funcion_encolar_evento)(), EVENTO_T ev);
void linea_serie_drv_enviar_array(char *buffer);
void linea_serie_drv_continuar_envio(char *buffer);
void funcion_callback(char letra);
void funcion_callback_fifo_encolar(void);


#endif
