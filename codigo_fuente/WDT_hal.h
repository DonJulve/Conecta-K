#ifndef WDTHAL_H
#define WDTHAL_H

#include <LPC210X.H>
#include <inttypes.h>
#include "llamadas_sistema.h"

void WDT_hal_inicializar(int sec);
void WDT_hal_feed(void);
void WDT_hal_test(void);

#endif
