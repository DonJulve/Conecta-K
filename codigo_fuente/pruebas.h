#ifndef PRUEBAS_H
#define PRUEBAS_H

#include <LPC210x.H>                       /* LPC210x definitions */
#include "temporizador_hal.h"
#include "temporizador_drv.h"
#include "Gestor_alarmas.h"
#include "gpio_hal.h"
#include "io_reserva.h"
#include "int_ext_drv.h"
#include "FIFO.h"


// Banco de pruebas del modulo Temporizador hal y drv
void prueba_timer0(void);

// Banco de pruebas del modulo GPIO
void prueba_gpio(void);

// Banco de pruebas del modulo colo FIFO
void prueba_fifo(void);

// Banco de pruebas del modulo Alarma
void prueba_alarma_software(void);
void alarma_1(void);
void alarma_2(void);
void alarma_3(void);
void alarma_4(void);
void alarma_5(void);

#endif
