/* guarda para evitar inclusiones m�ltiples ("include guard") */
#ifndef CONECTA_K_H_2023
#define CONECTA_K_H_2023

#include <inttypes.h>
#include "celda.h"
#include "tablero.h"
#include <stdint.h>

/* *****************************************************************************
 * declaracion de funciones visibles en el exterior conecta_K
 */

// función principal del juego
void conecta_K_jugar(void);

// funcion para comprobar el correcto funcionamiento
void conecta_K_verificar(void);

// devuelve la longitud de la línea más larga
uint8_t conecta_K_buscar_alineamiento_c(TABLERO *t, uint8_t fila,
	uint8_t columna, uint8_t color, int8_t delta_fila, int8_t
	delta_columna);

// devuelve true si encuentra una línea de longitud mayor o igual a 4
uint8_t conecta_K_hay_linea_c_c(TABLERO *t, uint8_t fila, uint8_t
	columna, uint8_t color);


// funciones a implementar en ARM

// devuelve la longitud de la línea más larga en un determinado sentido
uint8_t conecta_K_buscar_alineamiento_arm(TABLERO *t, uint8_t
	fila, uint8_t columna, uint8_t color, int8_t delta_fila, int8_t
	delta_columna);

// devuelve true si encuentra una línea de longitud mayor o igual a K
uint8_t conecta_K_hay_linea_arm_c(TABLERO *t, uint8_t fila, uint8_t
	columna, uint8_t color);

// devuelve true si encuentra una línea de longitud mayor o igual a K
uint8_t conecta_K_hay_linea_arm_arm (TABLERO *t, uint8_t fila, uint8_t
	columna, uint8_t color);
	
uint8_t conecta_K_hay_linea_arm_arm_op (TABLERO *t, uint8_t fila, uint8_t 
	columna, uint8_t color);



/* *****************************************************************************
 * declaración funciones internas conecta_K
 */

int conecta_K_verificar_K_en_linea(TABLERO *t, uint8_t fila, uint8_t columna, uint8_t color);

void conecta_K_test_cargar_tablero(TABLERO *t, uint8_t tablero_test[NUM_FILAS][NUM_COLUMNAS]);

void conecta_K_visualizar_tablero(TABLERO *t, uint8_t pantalla[NUM_FILAS+1][NUM_COLUMNAS+1]);

void conecta_K_visualizar_tablero_final(TABLERO* cuadricula, char buffer[2000]);

void conecta_K_previsualizar_tablero(TABLERO* cuadricula, char buffer[20000], int fila, int columna);


#endif /* CONECTA_K_H_2023 */
