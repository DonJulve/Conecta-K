#include <LPC210X.H>
#include "int_ext_drv.h"

static unsigned int estado_pulsacion_1 = NO_PULSADO;
static unsigned int estado_pulsacion_2 = NO_PULSADO;

static void (*FIFO_encolar)();

void inicializar_botones(void (*funcion_encolar_evento)(), uint32_t pr){
	eint1_init();
	eint2_init();
	alarma_activar(ALARMA_BOTONES, 0x80000064, 0);
	FIFO_encolar = funcion_encolar_evento;
}

void clear_nueva_pulsacion_1(void){
	eint1_clear_nueva_pulsacion();
}

unsigned int nueva_pulsacion_1(void){
	unsigned int new;
	new = eint1_read_nueva_pulsacion();
	eint1_clear_nueva_pulsacion(); // Las pulsaciones sólo deben procesarse una vez. Por tanto se pone a 0 después de leerlo
	return new;
}

void actualizar_estado_1(void){
	EXTINT =  EXTINT | (1<<1);        // clear interrupt flag de EINT1     
	if ((EXTINT & (1<<1)) != 0){ // si el botón está pulsado, la instrucción de arriba no hará nada y EXTINT valdrá 1. Si el botón no está pulsado valdrá 0
		estado_pulsacion_1 = PULSADO;
	}
	else{
		estado_pulsacion_1 = NO_PULSADO;
		// si no está pulsado se habilitan las interrupciones (antes ya se ha limpiado el de EXTINT)
		VICIntEnable = VICIntEnable | (1 << 15); // Enable EXTINT1 Interrupt (la interrupción del botón se deshabilita a si misma, al terminar la pulsación hay ue volver a habilitarla)
	}
}

unsigned int leer_estado_1(void){
	return estado_pulsacion_1; 
}


//EINT 2
void clear_nueva_pulsacion_2(void){
	eint2_clear_nueva_pulsacion();
}

unsigned int nueva_pulsacion_2(void){
	unsigned int new;
	new = eint2_read_nueva_pulsacion();
	eint2_clear_nueva_pulsacion(); // Las pulsaciones sólo deben procesarse una vez. Por tanto se pone a 0 después de leerlo
	return new;
}

void actualizar_estado_2(void){
	EXTINT =  EXTINT | (1<<2);        // clear interrupt flag de EINT1     
	if ((EXTINT & (1<<2)) != 0){ // si el botón está pulsado, la instrucción de arriba no hará nada y EXTINT valdrá 1. Si el botón no está pulsado valdrá 0
		estado_pulsacion_2 = PULSADO;
	}
	else{
		estado_pulsacion_2 = NO_PULSADO;
		// si no está pulsado se habilitan las interrupciones (antes ya se ha limpiado el de EXTINT)
		VICIntEnable = VICIntEnable | (1 << 16); // Enable EXTINT1 Interrupt (la interrupción del botón se deshabilita a si misma, al terminar la pulsación hay ue volver a habilitarla)
	}
}

unsigned int leer_estado_2(void){
	return estado_pulsacion_2; 
}


void gestion_boton(void){
	if(nueva_pulsacion_1() == 1){
		FIFO_encolar(ev_BOTON_1, 0);
	}
	if(nueva_pulsacion_2() == 1){
		FIFO_encolar(ev_BOTON_2, 0);
	}
}

void comprobar_botones(){
	actualizar_estado_1();
	if(leer_estado_1() == PULSADO){
		gestion_boton();
	}
	actualizar_estado_2();
	if(leer_estado_2() == PULSADO){
		gestion_boton();
	}
}
