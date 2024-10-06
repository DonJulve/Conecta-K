#include "pulsacion.h"
#include <LPC210x.H>                       /* LPC210x definitions */
#include "botones.h"

static unsigned int estado_pulsacion_0 = NO_PULSADO;


void clear_nueva_pulsacion_0(void){
	clear_nueva_pulsacion_eint0();
}

unsigned int nueva_pulsacion_0(void){
	unsigned int new;
	new = read_nueva_pulsacion_eint0();
	clear_nueva_pulsacion_eint0(); // Las pulsaciones sólo deben procesarse una vez. Por tanto se pone a 0 después de leerlo
	return new;
}



void actualizar_estado_0(void){
	EXTINT =  EXTINT | 1;        // clear interrupt flag de EINT0     
	if ((EXTINT & 1) == 1){ // si el botón está pulsado, la instrucción de arriba no hará nada y EXTINT valdrá 1. Si el botón no está pulsado valdrá 0
		estado_pulsacion_0 = PULSADO;
	}
	else{
		estado_pulsacion_0 = NO_PULSADO;
		// si no está pulsado se habilitan las interrupciones (antes ya se ha limpiado el de EXTINT)
		VICIntEnable = VICIntEnable | 0x00004000; // Enable EXTINT0 Interrupt (la interrupción del botón se deshabilita a si misma, al terminar la pulsación hay ue volver a habilitarla)
	}
}

unsigned int leer_estado_0(void){
	actualizar_estado_0();
	return estado_pulsacion_0; 
}