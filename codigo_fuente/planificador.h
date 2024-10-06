#ifndef PLANIFICADOR
#define PLANIFICADOR

#include <inttypes.h>
#include "io_reserva.h"
#include "FIFO.h"
#include "temporizador_drv.h"
#include "hello_world.h"
#include "power_hal.h"
#include "Gestor_alarmas.h"
#include "int_ext_drv.h"
#include "pruebas.h"
#include "juego.h"
#include "visualizar.h"
#include "linea_serie_drv.h"
#include "WDT_hal.h"

#define USUARIO_AUSENTE 12000

void planificador(void);
void desactivar_alarma_power_down(uint8_t *alarma_power_down_activa);
void reiniciar_alarma_power_down(uint8_t *alarma_power_down_activa);

#endif
