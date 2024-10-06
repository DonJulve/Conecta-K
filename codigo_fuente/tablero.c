#include "tablero.h"

void tablero_inicializar(TABLERO *t)
{
	size_t i, j;
	
	for(i = 0; i < NUM_FILAS; ++i){
		for(j = 0; j < MAX_NO_CERO; ++j) {
				t->columnas[i][j] = INVALIDO;
				celda_inicializar(&t->no_ceros[i][j]);
		}
	}
}

int tablero_insertar_celda(TABLERO *t, uint8_t fila, uint8_t columna, CELDA *c)
{
	
	size_t col = 0;
	// comprobar valided posición
	if( !tablero_fila_valida(fila) || !tablero_columna_valida(columna)) {
		return ERROR;
	}
	
	// comprobar valided celda
	if (c == NULL) {
		return ERROR;
	}
	
	//comprobar que este libre
	if (!celda_vacia(tablero_leer_celda(t, fila, columna))){
		return ERROR;
	}

	// encontrar primera posición libre en el vector
	// de columnas de la fila correspondiente
	for(; (col < MAX_NO_CERO) && (t->columnas[fila][col] != INVALIDO); ++col);

	// se ha llenado nuestra matriz estática
	if(MAX_NO_CERO == col) {
		return ERROR;
	}

	// inserción
	t->columnas[fila][col] = columna;
	t->no_ceros[fila][col] = *c;
	return EXITO;
}

int tablero_insertar_color(TABLERO *t, uint8_t fila, uint8_t columna, uint8_t color)
{
	
	size_t col = 0;
	
	// comprobar valided posición
	if( !tablero_fila_valida(fila) || !tablero_columna_valida(columna)) {
		return ERROR;
	}

	// comprobar valided color
	if (!tablero_color_valido(color)) {
		return ERROR;
	}

	//comprovar que este libre
	if (!celda_vacia(tablero_leer_celda(t, fila, columna))){
		return ERROR;
	}
	
	// encontrar primera posición libre en el vector
	// de columnas de la fila correspondiente
	for(; (col < MAX_NO_CERO) && (t->columnas[fila][col] != INVALIDO); ++col);

	// se ha llenado nuestra matriz estática
	if(MAX_NO_CERO == col) {
		return ERROR;
	}

	// inserción
	t->columnas[fila][col] = columna;
	celda_poner_valor(&t->no_ceros[fila][col], color);
	
	return EXITO;
}

int tablero_borrar_celda(TABLERO *t, uint8_t fila, uint8_t columna)
{
	
	size_t col = 0;
	
	// comprobar validez posición
	if( !tablero_fila_valida(fila) || !tablero_columna_valida(columna)) {
		return ERROR;
	}

	// hay que mirarlos todos
	for(; (col < MAX_NO_CERO) && (t->columnas[fila][col] != columna); ++col);

	if(col == MAX_NO_CERO) {
		return ERROR;
	}

	t->columnas[fila][col] = INVALIDO;
	celda_inicializar(&t->no_ceros[fila][col]);
	return EXITO;
}

CELDA 
tablero_leer_celda(const TABLERO *t, uint8_t fila, uint8_t columna)
{
	CELDA celda_invalida;
	size_t col = 0;

	// marcar celda como invalidad
	celda_inicializar(&celda_invalida);

	// comprobar validez posición
	if( !tablero_fila_valida(fila) || !tablero_columna_valida(columna)) {
		return celda_invalida;
	}

	// buscar si celda es valida
	for(; (col < MAX_NO_CERO) && (t->columnas[fila][col] != columna); ++col);

	if(col == MAX_NO_CERO) {
			return celda_invalida;
	}

	// devolver celda valida
	return t->no_ceros[fila][col];
}

int tablero_buscar_color(const TABLERO *t, uint8_t fila, uint8_t columna, uint8_t color)
{
	
	size_t col = 0;
	
	// comprobar validez posición
	if( !tablero_fila_valida(fila) || !tablero_columna_valida(columna)) {
		return ERROR;
	}

	// buscar columna en estructura dispersa
	for(; (col < MAX_NO_CERO) && (t->columnas[fila][col] != columna); ++col);

	if(col == MAX_NO_CERO) {
		return ERROR;
	}

	//si mismo color al que busco devolver encontrada
	if(celda_color(t->no_ceros[fila][col]) == color) {
		return EXITO;
	}
	
	// devolver error si posicion invalida y distinto color
	return ERROR;
}
