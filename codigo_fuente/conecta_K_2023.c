#include "conecta_K_2023.h"
#include "entrada.h"
#include "tablero_test.h"

extern uint8_t conecta_K_buscar_alineamiento_arm(TABLERO *t, uint8_t fila,
	uint8_t columna, uint8_t color, int8_t delta_fila, int8_t
	delta_columna);


extern uint8_t conecta_K_buscar_alineamiento_arm_op(TABLERO *t, uint8_t fila,
	uint8_t columna, uint8_t color, int8_t delta_fila, int8_t
	delta_columna);

extern uint8_t conecta_K_hay_linea_arm_c (TABLERO *t, uint8_t fila, uint8_t columna, uint8_t color);
extern uint8_t conecta_K_hay_linea_arm_arm_op (TABLERO *t, uint8_t fila, uint8_t columna, uint8_t color);
extern uint8_t conecta_K_hay_linea_arm_arm (TABLERO *t, uint8_t fila, uint8_t columna, uint8_t color);

// devuelve la longitud de la línea más larga en un determinado sentido
uint8_t conecta_K_buscar_alineamiento_c(TABLERO *t, uint8_t fila,
	uint8_t columna, uint8_t color, int8_t delta_fila, int8_t
	delta_columna)
{
	uint8_t nueva_fila;
	uint8_t nueva_columna;
		// comprobar si la celda es valida y del mismo color
		if (tablero_buscar_color(t, fila, columna, color) != EXITO) {
			return 0;
		}
		
    // encontrada, entonces avanzar índices
    nueva_fila = fila + delta_fila;
    nueva_columna = columna + delta_columna;

    // incrementar longitud y visitar celda vecina
    return 1 + conecta_K_buscar_alineamiento_c(t, nueva_fila, nueva_columna, color, delta_fila, delta_columna);
}

// devuelve true si encuentra una línea de longitud mayor o igual a _K
uint8_t
conecta_K_hay_linea_c_c(TABLERO *t, uint8_t fila, uint8_t columna, uint8_t color)
{
	 enum { N_DELTAS = 4};
   int8_t deltas_fila[N_DELTAS] = {0, -1, -1, 1};
   int8_t deltas_columna[N_DELTAS] = {-1, 0, -1, -1};
   unsigned int i = 0;
   uint8_t linea = FALSE;
   uint8_t long_linea = 0;

   // buscar linea en fila, columna y 2 diagonales
   for(i=0; (i < N_DELTAS) && (linea == FALSE); ++i) {
       // buscar sentido
       long_linea = conecta_K_buscar_alineamiento_c(t, fila, columna, color, deltas_fila[i], deltas_columna[i]);
       linea = long_linea >= K_SIZE;
       if (linea) {
         continue;
       }
       // buscar sentido inverso
       long_linea += conecta_K_buscar_alineamiento_c(t, fila-deltas_fila[i],
	       columna-deltas_columna[i], color, -deltas_fila[i], -deltas_columna[i]);
       linea = long_linea >= K_SIZE;
   }
   return linea;
}

uint8_t
conecta_K_hay_linea_c_arm(TABLERO *t, uint8_t fila, uint8_t columna, uint8_t color)
{
	 enum { N_DELTAS = 4};
   int8_t deltas_fila[N_DELTAS] = {0, -1, -1, 1};
   int8_t deltas_columna[N_DELTAS] = {-1, 0, -1, -1};
   unsigned int i = 0;
   uint8_t linea = FALSE;
   uint8_t long_linea = 0;

   // buscar linea en fila, columna y 2 diagonales
   for(i=0; (i < N_DELTAS) && (linea == FALSE); ++i) {
       // buscar sentido
       long_linea = conecta_K_buscar_alineamiento_arm(t, fila, columna, color, deltas_fila[i], deltas_columna[i]);
       linea = long_linea >= K_SIZE;
       if (linea) {
         continue;
       }
       // buscar sentido inverso
       long_linea += conecta_K_buscar_alineamiento_arm(t, fila-deltas_fila[i],
	       columna-deltas_columna[i], color, -deltas_fila[i], -deltas_columna[i]);
       linea = long_linea >= K_SIZE;
   }
   return linea;
}


uint8_t
conecta_K_hay_linea_c_arm_op(TABLERO *t, uint8_t fila, uint8_t columna, uint8_t color)
{
	 enum { N_DELTAS = 4};
   int8_t deltas_fila[N_DELTAS] = {0, -1, -1, 1};
   int8_t deltas_columna[N_DELTAS] = {-1, 0, -1, -1};
   unsigned int i = 0;
   uint8_t linea = FALSE;
   uint8_t long_linea = 0;

   // buscar linea en fila, columna y 2 diagonales
   for(i=0; (i < N_DELTAS) && (linea == FALSE); ++i) {
       // buscar sentido
       long_linea = conecta_K_buscar_alineamiento_arm_op(t, fila, columna, color, deltas_fila[i], deltas_columna[i]);
       linea = long_linea >= K_SIZE;
       if (linea) {
         continue;
       }
       // buscar sentido inverso
       long_linea += conecta_K_buscar_alineamiento_arm_op(t, fila-deltas_fila[i],
	       columna-deltas_columna[i], color, -deltas_fila[i], -deltas_columna[i]);
       linea = long_linea >= K_SIZE;
   }
   return linea;
}

// carga el estado a mitad de partida de las primeras 7 filas y columnas 
// a la estructura de datos tablero para facilitar el test de posibles jugadas
//
// 0: casilla vacia, 1:ficha jugador uno, 2: ficha jugador dos
void conecta_K_test_cargar_tablero(TABLERO *t, uint8_t tablero_test[NUM_FILAS][NUM_COLUMNAS])
{
	//#include "tablero_test.h"	
	int i,j;
	for (i = 0; i < NUM_FILAS; i++){
		for (j = 0; j < NUM_COLUMNAS; j++){
			if (tablero_test[i][j] != 0){
				tablero_insertar_color(t, i, j, tablero_test[i][j]);
			}
		}

	}
	//for... for... tablero_insertar_color...

}

// funcion que visualiza en "pantalla" el contenido de las 7 primeras filas y columnas 
// de las m*n del tablero en juego (suponemos que m y n son >= 7 siempre)
// en memoria se deberia ver algo tal que asi:
// 00 C1 C2 C3 C4 C5 C6 C7
// F1 00 00 00 00 00 00 00
// F2 00 00 11 00 00 00 00
// F3 00 11 22 22 00 00 00
// F4 00 00 11 00 00 00 00
// F5 00 00 00 00 00 00 00
// F6 00 00 00 00 00 00 00
// F7 00 00 00 00 00 00 00 
void conecta_K_visualizar_tablero(TABLERO *t, uint8_t pantalla[NUM_FILAS+1][NUM_COLUMNAS+1])
{
	//La pantalla está en 3C
	uint8_t col = 193;	// 193 = 0xC1
	uint8_t fil = 241;	// 241 = 0XF1
	
	int i, j;
	for (i = 0; i < NUM_FILAS+1; i++){
		for (j = 0; j < NUM_COLUMNAS+1; j++){
			if ( i == 0 && j == 0) {
				pantalla[0][0] = 0xFC;	// Casilla superior izquierda
			}
			else if (i == 0 && j != 0) {
				pantalla[0][j] = col;		// Coloca Cx
				col++;
			}
			else if (i != 0 && j == 0){
				pantalla[i][0] = fil;		// Coloca Fx
				fil++;
			}
			else{
				uint8_t color = celda_color(tablero_leer_celda(t, i-1, j-1));
				if (color == 1){		// es blanca
					pantalla[i][j] = 0x11;
				}
				else if (color == 2){	// es negra
					pantalla[i][j] = 0x22;
				}
			}
		}
	}
}  

//
int conecta_K_verificar_K_en_linea(TABLERO *t, uint8_t fila, uint8_t columna, uint8_t color){
	// en esta funcion es donde se debe verificar que todas las optimizaciones dan el mismo resultado
	uint8_t resultado_c_c = conecta_K_hay_linea_c_c(t, fila, columna, color);
	uint8_t resultado_c_arm = conecta_K_hay_linea_c_arm(t, fila, columna, color);
	uint8_t resultado_c_arm_op = conecta_K_hay_linea_c_arm_op(t, fila, columna, color);
	uint8_t resultado_arm_c = conecta_K_hay_linea_arm_c(t, fila, columna, color);
	uint8_t resultado_arm_arm = conecta_K_hay_linea_arm_arm(t, fila, columna, color);
	uint8_t resultado_arm_arm_op = conecta_K_hay_linea_arm_arm_op(t, fila, columna, color);
	if(resultado_c_c != resultado_c_arm || resultado_c_c != resultado_c_arm_op || resultado_c_c != resultado_arm_c || 
			resultado_c_c != resultado_arm_arm_op || resultado_c_c != resultado_arm_arm_op) 
		while(1);
	return resultado_c_c;
}


int verificar_jugada (TABLERO* cuadricula, uint8_t row, uint8_t column, uint8_t colour, uint8_t salida[NUM_FILAS+1][NUM_COLUMNAS+1]){
		int correcto = 0;
		//validada la entrada en rango, mirar color valido?
		if(tablero_fila_valida(row) && tablero_columna_valida(column) && tablero_color_valido(colour)){	
			//podriamos no validarla ya que tablero_insertar_valor vuelve a validar
 			if (celda_vacia(tablero_leer_celda(cuadricula, row, column))){
				//tablero_insertar tambien chequea si esta libre esa celda o no...
				if(tablero_insertar_color(cuadricula, row, column, colour) == EXITO) {
					conecta_K_visualizar_tablero(cuadricula, salida);
					if(conecta_K_verificar_K_en_linea(cuadricula, row, column, colour)) {
						correcto = 1;
					}
					else {
						correcto = 0;
					}
				}
				else {
					correcto = 0;
				}
			}
			//else: celda no vacia
		}
		return correcto;
}

void conecta_K_verificar(void){
		
	#include "tablero_test.h"	
	
	// 8x8 intentando que este alineada para que se vea bien en memoria
	static uint8_t salida[NUM_FILAS+1][NUM_COLUMNAS+1];
	static uint8_t num_aciertos = 0;
	static uint8_t num_fallos = 0;
	static uint8_t fallos[NUM_CASOS];
	TABLERO cuadricula;

	uint8_t row, column, colour;
	
	int i = 0;
	for (i = 0; i < NUM_CASOS; i++){
		tablero_inicializar(&cuadricula);

		conecta_K_test_cargar_tablero(&cuadricula, matriz_vector[i]);
		conecta_K_visualizar_tablero(&cuadricula, salida);
		
		entrada_leer(movimientos[i], &row, &column, &colour);
		if(verificar_jugada(&cuadricula, row, column, colour,salida)){
			num_aciertos++;
		}
		else {
			fallos[i] = i + 1;
			num_fallos++;
		}
	}
	
	if (num_aciertos == NUM_CASOS){
		while(1);
	}

	if (fallos[0] != 0 || num_fallos != 0){
		while(1);
	}
}

void conecta_K_visualizar_tablero_final(TABLERO* cuadricula, char buffer[20000]){
	
	//La pantalla está en 3C
	char col = '1';	// 193 = 0xC1
	char fil = '1';	// 241 = 0XF1

    int i, j;
    uint32_t offset = 0;
		buffer[offset++] = '\n';
    for (i = 0; i < NUM_FILAS + 1; i++) {
        for (j = 0; j < NUM_COLUMNAS + 1; j++) {
            if (i == 0 && j == 0) {
                buffer[offset++] = '-';
								buffer[offset++] = '|';
            } else if (i == 0 && j != 0) {
                buffer[offset++] = col;
								buffer[offset++] = '|';
                col++;
            } else if (i != 0 && j == 0) {
                buffer[offset++] = fil;
								buffer[offset++] = '|';
                fil++;
            } else {
                uint8_t color = celda_color(tablero_leer_celda(cuadricula, i - 1, j - 1));
                if (color == 1) {    // es blanca
                    buffer[offset++] = 'B';
										buffer[offset++] = '|';
                } else if (color == 2) {    // es negra
                    buffer[offset++] = 'N';
										buffer[offset++] = '|';
                }
								else{
									buffer[offset++] = ' ';
									buffer[offset++] = '|';
								}
            }
        }
        buffer[offset++] = '\n';
    }
		buffer[offset++] = '\n';
		buffer[offset++] = '\0';
}  

void conecta_K_previsualizar_tablero(TABLERO* cuadricula, char buffer[20000], int fila, int columna){
	
	//La pantalla está en 3C
	char col = '1';	// 193 = 0xC1
	char fil = '1';	// 241 = 0XF1

    int i, j;
    uint32_t offset = 0;
		buffer[offset++] = '\n';
    for (i = 0; i < NUM_FILAS + 1; i++) {
        for (j = 0; j < NUM_COLUMNAS + 1; j++) {
            if (i == 0 && j == 0) {
                buffer[offset++] = '-';
								buffer[offset++] = '|';
            } else if (i == 0 && j != 0) {
                buffer[offset++] = col;
								buffer[offset++] = '|';
                col++;
            } else if (i != 0 && j == 0) {
                buffer[offset++] = fil;
								buffer[offset++] = '|';
                fil++;
            } else {
								uint8_t color = celda_color(tablero_leer_celda(cuadricula, i - 1, j - 1));
								if ((i - 1) == fila && (j - 1) == columna){
									buffer[offset++] = '#';
									buffer[offset++] = '|';
								}
								else if (color == 1) {    // es blanca
									buffer[offset++] = 'B';
									buffer[offset++] = '|';
                } 
								else if (color == 2) {    // es negra
                  buffer[offset++] = 'N';
									buffer[offset++] = '|';
                }
								else{
									buffer[offset++] = ' ';
									buffer[offset++] = '|';
								}
            }
        }
        buffer[offset++] = '\n';
    }
		buffer[offset++] = '\n';
		buffer[offset++] = '\0';
}  

void conecta_K_jugar(void){	
	
	// new, row, column, colour, padding to prevent desalinating to 8 bytes
	static volatile uint8_t entrada[8] = {0, 0, 0, 0, 0, 0, 0, 0 }; //jugada, fila, columna, color, ...
	// 8x8 intentando que este alineada para que se vea bien en memoria
	static uint8_t salida[NUM_FILAS+1][NUM_COLUMNAS+1];
	
	TABLERO cuadricula;

	uint8_t row, column, colour;

	tablero_inicializar(&cuadricula);

	conecta_K_test_cargar_tablero(&cuadricula, tablero_test);
	conecta_K_visualizar_tablero(&cuadricula, salida);

	entrada_inicializar(entrada);
	
	while (1){
		while (entrada_nueva(entrada) == 0){}; 
			// insertar_entrada(t, fila_leer, columna_leer)
		entrada_leer(entrada, &row, &column, &colour);
		//validada la entrada en rango, mirar color valido?
		if(tablero_fila_valida(row) && tablero_columna_valida(column) && tablero_color_valido(colour)){	
			//podriamos no validarla ya que tablero_insertar_valor vuelve a validar
 			if (celda_vacia(tablero_leer_celda(&cuadricula, row, column))){
				//tablero_insertar tambien chequea si esta libre esa celda o no...
				if(tablero_insertar_color(&cuadricula, row, column, colour) == EXITO) {
					conecta_K_visualizar_tablero(&cuadricula, salida);
					if(conecta_K_verificar_K_en_linea(&cuadricula, row, column, colour)) {
						while(1); // equivaldria a K_linea encontrada, fin de partida... 
					}
				}
				else {
					while(1); //no cabe en la matriz dispersa, hemos dimensionado mal, error de diseño
				}
			}
			//else: celda no vacia
		}
		//else: fuera de rango fila, columna o color
		entrada_inicializar (entrada);
	}
}

