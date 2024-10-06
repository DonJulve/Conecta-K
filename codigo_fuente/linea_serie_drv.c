#include "linea_serie_drv.h"

static void (*FIFO_encolar)();											// Callback para la funcion FIFO_encolar.h
static EVENTO_T evento;
static char buffer_comandos[MAX_BUFFER_SIZE];      // Buffer para almacenar los caracteres recibidos
static int UART0_counter;  
static int comando_valido;
static GPIO_HAL_PIN_T pin_serie_error;
static GPIO_HAL_PIN_T numero_pines_serie_error;

void linea_serie_drv_inicializar(GPIO_HAL_PIN_T pin_s, GPIO_HAL_PIN_T numero_pines_s, void (*funcion_encolar_evento)(), EVENTO_T ev) {
	pin_serie_error = pin_s;
	UART0_counter = 0;
	comando_valido = 0;
	numero_pines_serie_error = numero_pines_s;
	FIFO_encolar = funcion_encolar_evento;
	evento = ev;
	gpio_hal_sentido(pin_s, numero_pines_s, GPIO_HAL_PIN_DIR_OUTPUT);
	linea_serie_hal_init(&funcion_callback, &funcion_callback_fifo_encolar);
}

void linea_serie_recibir_char(char c){
		if (comando_valido == 1){
			if(c == '!'){
				if (UART0_counter == 3) {
					uint32_t aux;
					aux = (buffer_comandos[0] << 16) | (buffer_comandos[1] << 8) | (buffer_comandos[2]); 
					FIFO_encolar(evento, aux);
				}
				else{
					gpio_hal_escribir(pin_serie_error, numero_pines_serie_error, 1);
				}
				UART0_counter = 0;
				buffer_comandos[0] = buffer_comandos[1] = buffer_comandos[2] = 0;
				comando_valido = 0;
				linea_serie_drv_enviar_array("!\n");
				return;
			}
			else if (c != '$'){
				if(UART0_counter < 3){
					buffer_comandos[UART0_counter] = c;
					UART0_counter++;
				}
				else{
					gpio_hal_escribir(pin_serie_error, numero_pines_serie_error, 1);
					comando_valido = 0;
				}
			}
			else{
				linea_serie_drv_enviar_array("\n");
			}
		}
		if (c == '$'){
			UART0_counter = 0;
			comando_valido = 1;
			gpio_hal_escribir(pin_serie_error, numero_pines_serie_error, 0);
		}
	linea_serie_drv_enviar_array(&c);
	if(comando_valido == 0){
		gpio_hal_escribir(pin_serie_error, numero_pines_serie_error, 1);
		linea_serie_drv_enviar_array("\n");
	}
}


void linea_serie_drv_enviar_array(char *buffer){
	linea_serie_hal_enviar_array(buffer);
	linea_serie_hal_continuar_envio();
}


void linea_serie_drv_continuar_envio(char *buffer){
	linea_serie_hal_continuar_envio();
}


void funcion_callback(char letra){
	linea_serie_recibir_char(letra);
}

void funcion_callback_fifo_encolar(void) {
	FIFO_encolar(ev_TX_SERIE, 0);
}
