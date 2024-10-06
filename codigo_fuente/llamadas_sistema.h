
#ifndef LLAMADAS_SISTEMAS_H
#define LLAMADAS_SISTEMAS_H

#include <inttypes.h>

static uint32_t registro_especia = 0;

uint8_t __swi(0xFC) read_IRQ_bit(void);
void __swi(0xFD) disable_fiq(void);
void __swi(0xFE) disable_irq(void);
void __swi(0xFF) enable_irq (void);

#endif
