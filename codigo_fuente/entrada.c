#include "entrada.h"

/* *****************************************************************************
 * macros internas acceso a la E/S 
 * modificando el contenido de la memoria desde el depurador
 */

//marcar que ya se ha realizado la jugada
void entrada_inicializar(volatile uint8_t entrada[ALIGN_8]) {
		entrada[0] = 0; //nueva
		entrada[1] = 0; //fila
		entrada[2] = 0; //columna
		entrada[3] = 0; //color
}


//hay nueva jugada? (alguien ha modificado asincronamente el contenido de memoria) 
uint8_t entrada_nueva(volatile uint8_t entrada[ALIGN_8]) { 
	return entrada[0];
}

//leer fila / columna / color
void entrada_leer(volatile uint8_t entrada[ALIGN_8], uint8_t *fila, uint8_t *columna, uint8_t *color) {
	// restamos 1 porque el humano juega de 1..m, pero el formato interno va de 0..(m-1)
	*fila = entrada[1] - 1;
	*columna = entrada[2] - 1;
	*color = entrada[3];
}


