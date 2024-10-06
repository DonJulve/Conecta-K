#ifndef __ENTRADA_H__
#define __ENTRADA_H__

#include <inttypes.h>

enum {ALIGN_8 = 8};

//marcar que ya se ha realizado la jugada
void entrada_inicializar(volatile uint8_t entrada[ALIGN_8]);

//hay nueva jugada? (alguien ha modificado asincronamente el contenido de memoria) 
uint8_t entrada_nueva(volatile uint8_t entrada[ALIGN_8]);

//leer fila / columna 0..n-1
void entrada_leer(volatile uint8_t entrada[ALIGN_8], uint8_t *fila, uint8_t *columna, uint8_t *color);

#endif
