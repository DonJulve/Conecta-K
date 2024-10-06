#ifndef BOTONES_H
#define BOTONES_H

#include "int_ext_hal.h"
#include "eventos.h"
#include "Gestor_alarmas.h"

enum {
	PULSADO = 0,
	NO_PULSADO = 1
};

void inicializar_botones(void (*funcion_encolar_evento)(), uint32_t pr);
unsigned int nueva_pulsacion_1(void);
void clear_nueva_pulsacion_1(void);
void actualizar_estado_1(void);
unsigned int leer_estado_1(void);
unsigned int nueva_pulsacion_2(void);
void clear_nueva_pulsacion_2(void);
void actualizar_estado_2(void);
unsigned int leer_estado_2(void);
void gestion_boton(void);
void comprobar_botones(void);

#endif
