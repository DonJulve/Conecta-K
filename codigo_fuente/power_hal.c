#include "power_hal.h"

void power_hal_wait(void) {
	PCON = 0x01;		// Entre en modo idle
}

void power_hal_deep_sleep(void)  {

  EXTWAKE = 0x6; 	// EINT1 Y EINT2 despierta
	PCON |= 0x02; 	// Power_down
	
	// Recupera la velocidad del reloj de 60 MHz
	PLLFEED = 0xAA;
	PLLFEED = 0x55;
	EXTWAKE = 0; 
}
