#ifndef VISUALIZAR_H
#define VISUALIZAR_H

#include "gpio_hal.h"


void inicializar_visualizar(GPIO_HAL_PIN_T pin_v, GPIO_HAL_PIN_T numero_pines_v, GPIO_HAL_PIN_T pin_w, GPIO_HAL_PIN_T numero_pines_w);
void visualizar_cuenta(uint32_t cuenta);
void visualizar_hello_world(uint32_t cuenta);

#endif
