#include "int_ext_hal.h"

// variable para comprobar que se hacen las interrupciones que deberían hacerse
static volatile int eint1_cuenta = 0;
// variable que se activa al detectar una nueva pulsación
static volatile int eint1_nueva_pulsacion = 0;

static volatile int eint2_cuenta = 0;
static volatile int eint2_nueva_pulsacion = 0;

void inicializar_pines(void){
	PINSEL0 = 0xA0000000;
	PINSEL1 = 0x00000000;
}

void eint1_ISR (void) __irq {
	eint1_cuenta++;
	VICIntEnClr = (1 << 15);    //deshabilitamos eint1
	EXTINT =  EXTINT | (1<<1);        // clear interrupt flag        
	VICVectAddr = 0;             // Acknowledge Interrupt
	eint1_nueva_pulsacion = 1;
}

void eint1_clear_nueva_pulsacion(void){
	eint1_nueva_pulsacion = 0;
};

unsigned int eint1_read_nueva_pulsacion(){
	return eint1_nueva_pulsacion;
};

unsigned int eint1_read_cuenta(){
	return eint1_cuenta;
};

void eint1_init (void) {
	inicializar_pines();
	eint1_nueva_pulsacion = 0;
	eint1_cuenta = 0;
	EXTINT =  EXTINT | (1<<1);        // clear interrupt flag     	
	// configuration of the IRQ slot number 2 of the VIC for EXTINT1
	VICVectAddr2 = (unsigned long)eint1_ISR;          // set interrupt vector in 0
    // 0x20 bit 5 enables vectored IRQs. 
		// 14 is the number of the interrupt assigned. Number 14 is the EINT0 (see table 40 of the LPC2105 user manual  
		// 15 EINT1
		// 16 EINT2
	VICVectCntl2 = 0x20 | 15;                   
  VICIntEnable = VICIntEnable | (1 << 15);                  // Enable EXTINT1 Interrupt
}

//EINT 2

void eint2_ISR (void) __irq {
	eint2_cuenta++;
	VICIntEnClr = (1 << 16);    //deshabilitamos eint2
	EXTINT =  EXTINT | (1<<2);        // clear interrupt flag        
	VICVectAddr = 0;             // Acknowledge Interrupt
	eint2_nueva_pulsacion = 1;
}

void eint2_clear_nueva_pulsacion(void){
	eint2_nueva_pulsacion = 0;
};

unsigned int eint2_read_nueva_pulsacion(){
	return eint2_nueva_pulsacion;
};

unsigned int eint2_read_cuenta(){
	return eint2_cuenta;
};

void eint2_init (void) {
	inicializar_pines();
	eint2_nueva_pulsacion = 0;
	eint2_cuenta = 0;
	EXTINT =  EXTINT | (1<<2);        // clear interrupt flag     	
	// configuration of the IRQ slot number 2 of the VIC for EXTINT1
	VICVectAddr3 = (unsigned long)eint2_ISR;          // set interrupt vector in 0
    // 0x20 bit 5 enables vectored IRQs. 
		// 14 is the number of the interrupt assigned. Number 14 is the EINT0 (see table 40 of the LPC2105 user manual  
		// 15 EINT1
		// 16 EINT2
	VICVectCntl3 = 0x20 | 16;                   
  VICIntEnable = VICIntEnable | (1 << 16);                  // Enable EXTINT1 Interrupt
}
