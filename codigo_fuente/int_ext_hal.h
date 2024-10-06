#ifndef INT_EXT_HAL_H
#define INT_EXT_HAL_H

#include <LPC210x.H>

void inicializar_pines(void);
void eint1_ISR (void) __irq;
void eint1_clear_nueva_pulsacion(void);
unsigned int eint1_read_nueva_pulsacion(void);
unsigned int eint1_read_cuenta(void);
void eint1_init (void);
void eint2_ISR (void) __irq;
void eint2_clear_nueva_pulsacion(void);
unsigned int eint2_read_nueva_pulsacion(void);
unsigned int eint2_read_cuenta(void);
void eint2_init (void);

#endif
