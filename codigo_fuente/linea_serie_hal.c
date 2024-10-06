#include "linea_serie_hal.h"


static void (*callback_enviar)(char);	// Funcion callback para pasar la letra leida
static void (*callback_encolar)();		// Funcion callback para encolar evento
static int index;
static char buffer[2000];

void UART0_ISR(void) __irq{
	VICVectAddr = 0;
	if((U0IIR & 0x0E) == 0x04){
		char c = U0RBR;
		callback_enviar(c);
	}
	else {
		linea_serie_hal_continuar_envio();
	}
}

void linea_serie_hal_init(void (*funcion_callback_enviar)(char), void (*funcion_callback_encolar)()){
	
		callback_enviar = funcion_callback_enviar;
		callback_encolar = funcion_callback_encolar;
		PINSEL0 |= 0x5;
    U0LCR = 0x83;  // DLAB = 1 para permitir la escritura a registros DLL y DLM
    U0DLL = 97;    // Valor para 9600 bps con un reloj de 12MHz
    U0DLM = 0;
    U0LCR = 0x03;  // DLAB = 0 para deshabilitar la escritura a registros DLL y DLM
		U0IER = 3;
	
		VICVectCntl4 = 0x20 | 6;
		VICVectAddr4 = (unsigned long) UART0_ISR;
		VICIntEnable = VICIntEnable | 0x00000040;
	
		index = 0;
	
}

void linea_serie_hal_enviar_array(char comando[]){
	index = 0; 																	//Inicializaci?n de variable estatica
	memset(buffer, 0, 2000); 								//Inicializo el buffer estatico
	strcpy(buffer, comando);							 	//Copio el comando en el buffer estático
	/*
	if (buffer[0] == '\0'){	//Si se quiere enviar una cadena vacía
		callback_encolar();
	}
	else{
		U0THR = buffer[index]; 											//Envio el primer caracter y actualizo el indice
		index++;
	}
	*/
}

void linea_serie_hal_continuar_envio(void){
	if(buffer[index] == '\0'){									//Si llegamos al final del buffer
		callback_encolar();
	}
	else{
		U0THR = buffer[index];										//Si no, seguimos enviando caracteres
		index++;
	}
}


