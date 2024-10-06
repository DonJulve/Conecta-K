
#include "pruebas.h"


// Banco de pruebas del modulo Temporizador hal y drv
void prueba_timer0(void){

		unsigned int time = 0;
    temporizador_drv_iniciar(); // Inicia el temporizador

    // Prueba de temporizador_hal_empezar
    temporizador_drv_empezar(); // Inicia el contador
	
		while (time != 2000000){
			time = temporizador_drv_leer();
		}
}


// Banco de pruebas del modulo GPIO
void prueba_gpio(void){
	GPIO_HAL_PIN_T inicio;
	gpio_hal_iniciar();
	
	inicio = 22;
	gpio_hal_sentido(22, 2, GPIO_HAL_PIN_DIR_OUTPUT);
	if(IODIR != 0x00C00000)
		while(1);
	
	inicio = 6;
	gpio_hal_sentido(6,2,GPIO_HAL_PIN_DIR_OUTPUT);
	if(IODIR != 0x00C000C0)
		while(1);
	
	inicio = 16;
	gpio_hal_sentido(inicio,2,GPIO_HAL_PIN_DIR_INPUT);
	if(IODIR != 0x00C000C0)
		while(1);
	
	inicio = 22;
	gpio_hal_escribir(inicio, 2, 3);
	if(IOSET != 0x00C00000)
		while (1);
	
	inicio = 6;
	gpio_hal_escribir(inicio,2,2);
	if(IOSET != 0x00C00080)
		while (1);
}


// Banco de pruebas del modulo colo FIFO
void prueba_fifo(void){
	int i;
	uint8_t resultado;
	
	EVENTO_T miEvento = TIMER0;
	uint32_t datosAuxiliares;  // Variable para almacenar los datos extraídos

	FIFO_inicializar(GPIO_OVERFLOW, GPIO_OVERFLOW_BITS);
	
//Para comprobar funcionamiento de la cola
	//Inicializamos la cola y declaramos las variables
	
	//Intentamos extraer de la cola vacía
	if (FIFO_extraer(&miEvento,&datosAuxiliares)!=0){
		while(1); //Si nos quedamos aquí, FIFO_extraer() va mal
	}
	
	for (i=0; i<31; i++) {
		FIFO_encolar(TIMER0,0);				//Encolamos 31 eventos de tipo TIMER0 
	}
	
	FIFO_encolar(TIMER1,0);					//En este punto la cola está llena
	//FIFO_encolar(TIMER1,0);				//Si descomentamos esta instrucción entramos en un bucle infinito

	if (FIFO_estadisticas(VOID) != 32) {
			while(1);										//Si entramos aquí ha habido un fallo
	}
	if (FIFO_estadisticas(TIMER0) != 31) {
			while(1);										//Si entramos aquí ha habido un fallo
	}
	resultado = FIFO_extraer(&miEvento, &datosAuxiliares); //resultado es el número de eventos en cola actualmente
	if (resultado != 1) {
		while(1); //Si nos quedamos aqui fallo al extraer
	}

	FIFO_encolar(TIMER1,0);
	
	if (FIFO_estadisticas(VOID) != 33) {
		while(1); //Si nos quedamos aqui ha habido un fallo
	}
}	



// Banco de pruebas del modulo Alarma
void prueba_alarma_software(void) {
	gpio_hal_sentido(0, 2, GPIO_HAL_PIN_DIR_OUTPUT);
	alarma_activar(ALARMA_1, 0x80000005, 0);
	alarma_activar(ALARMA_2, 0x00000006, 0);
	alarma_activar(ALARMA_3, 0x0000000B, 0);
	alarma_activar(ALARMA_4, 0x0000000B, 0);
}

void alarma_1(void){
	static uint8_t contador = 1;
	IOCLR = 0xff;
	gpio_hal_escribir(GPIO_HELLO_WORLD,GPIO_HELLO_WORLD_BITS,contador);
	contador++;
}

void alarma_2(void){
	if (IOSET != 1) {
		while (1);	// Si se queda aqui falla
	}
}

void alarma_3(void){
	if (IOSET != 2) {
		while (1);	// Si se queda aqui falla
	}	
	IOCLR = 0xff;
}


void alarma_4(void){
	alarma_activar(ALARMA_1, 0, 0);
	alarma_activar(ALARMA_5, 0x000000010, 0);
}

void alarma_5(void) {
	if (IOSET != 0) {
		while (1);	// Si se queda aqui falla
	}	
	
	// Se pueden guardar
	alarma_activar(ALARMA_5, 0x80000010, 0);
	alarma_activar(ALARMA_5, 0x80000010, 0);
	alarma_activar(ALARMA_5, 0x80000010, 0);
	alarma_activar(ALARMA_5, 0x00000010, 0);
	
	// Desbordamiento
	alarma_activar(ALARMA_4, 0x000000010, 0);
}


