//Tipo Abstraco de Datos para encapsular un tablero

#ifndef __TABLERO_H__
#define __TABLERO_H__

#include <stddef.h>
#include <stdint.h>

#include "celda.h"
#include "config_conecta_K.h"


enum { MAX_NO_CERO = 6, // máximo número de celdas no vacías por columna
    INVALIDO = 255 // indica si una celda es inválida
};

enum { EXITO = 0,
    ERROR = -1,
    FALSE = 0,
    TRUE = 1};

typedef uint8_t COLUMNA[MAX_NO_CERO];
typedef CELDA NO_CERO[MAX_NO_CERO];

// Un tablero disperso se almacena como 2 listas:
// a) la lista columnas almacena los índices de las columnas que para 
//    la fila iesima tienen valores no-cero (celdas no vacías)
// b) la lista no_ceros almacena los valores de las celdas no vacías.
//
// Por ejemplo, si un tablero t solo tiene la celda ocupada de la posición 3, 4 entonces
// t.columnas[3][0] será igual a 4 y t.no_ceros[3][0] tendrá el valor de la celda
//
// Propiedades: dentro de una fila, no es necesario que los índices de las columnas estén
// ordenados, dependera del orden de insercion.
//
// Opcional: 1) asegurar que los vectores siempre están ordenados
//           2) emplear punteros y tener un pool de elementos COLUMNA y NO_CERO
typedef struct {
    COLUMNA columnas[NUM_FILAS];
    NO_CERO no_ceros[NUM_FILAS];
} TABLERO;

// tablero denso de celdas, no lo usamos
// typedef CELDA TABLERO_DENSO[NUM_FILAS][NUM_COLUMNAS];

// inicializar la estructura estatica TABLERO

void tablero_inicializar(TABLERO *t);

// devuelve 0 si correcto, -1 en caso contrario
int tablero_insertar_celda(TABLERO *t, uint8_t fila, uint8_t columna, CELDA *c);

// devuelve 0 si correcto, -1 en caso contrario
int tablero_insertar_color(TABLERO *t, uint8_t fila, uint8_t columna, uint8_t color);

// devuelve 0 en caso de exito, -1 en caso contrario
int tablero_borrar_celda(TABLERO *t, uint8_t fila, uint8_t columna);

// devuelve 0 cuando el color de la celda en el tablero para la posición
// fila columna coincide con los parametros de entrada
int tablero_buscar_color(const TABLERO *t, uint8_t fila, uint8_t columna, uint8_t color);

// nos devuelve una determinada celda 
CELDA tablero_leer_celda(const TABLERO *t, uint8_t fila, uint8_t columna);

// funciones de comprobación de rangos

//la columna es valida?
static uint8_t tablero_columna_valida(uint8_t columna) {
	return columna < NUM_COLUMNAS;
};

// la fila es valida?
static uint8_t tablero_fila_valida(uint8_t fila) {
  return fila < NUM_FILAS;
};

// el color es valido?
static uint8_t tablero_color_valido(uint8_t color) {
	return (color==1 || color == 2);
};
#endif // __TABLERO_H__
