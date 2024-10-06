#include "WDT_hal.h"

void WDT_hal_inicializar(int sec) {
    // Configurar el registro WDTC para determinar el tiempo de timeout
    WDTC = sec * 1000000;  // Configurar el timeout en microsegundos (1 segundo = 1000000 microsegundos)

    // Configurar el registro WDMOD para habilitar el watchdog
    WDMOD = 0x3;  // Bit 0: WDEN (habilitar el watchdog), Bit 1: WDRESET (generar un reset al expirar el temporizador)

    // Reiniciar el contador del watchdog para evitar que se realice un reinicio no deseado
    WDFEED = 0xAA;
    WDFEED = 0x55;
}

void WDT_hal_feed(void) {
    // Alimentar el watchdog escribiendo secuencias específicas en los registros WDFEED
	
		uint8_t bit_IRQ = 0;
		bit_IRQ = read_IRQ_bit();
		if ( bit_IRQ == 0) {	// ACTIVAS -> DESACTIVAR
			disable_irq();
		}
		
    WDFEED = 0xAA;
    WDFEED = 0x55;
		
		bit_IRQ = read_IRQ_bit();
		if ( bit_IRQ == 1) {	// ACTIVAS -> DESACTIVAR
		// LUEGO VOLVER A ACTIVAR
			enable_irq();
		}
}

void WDT_hal_test(void) {
		WDT_hal_feed();
    WDT_hal_feed();
    WDT_hal_feed();
    while (1) {
        // Entrar en un bucle infinito sin alimentar el watchdog
        // Esto debería resultar en un reinicio del sistema después de que expire el temporizador del watchdog
    }
}
