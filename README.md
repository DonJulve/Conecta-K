# Implementación de Juego ConectaK en Sistemas Embebidos

El proyecto desarrolla un sistema de juego estratégico (Conecta K) para sistemas embebidos, utilizando diversos periféricos y temporizadores para interactuar con el procesador y el usuario. El sistema cuenta con una interfaz gráfica de entrada/salida agradable a través de UART0, botones configurados como líneas de interrupción externa, y un planificador de eventos eficiente.

## Tecnologías Utilizadas

- **Lenguaje de programación C** para el desarrollo de los módulos y control de periféricos.
- **Controlador de interrupciones (VIC)** para manejar eventos específicos y controlar el flujo del programa.
- **Temporizadores y Watchdog** para medir tiempos, generar retardos precisos, y restablecer el procesador en caso de mal funcionamiento.
- **GPIO** para simular dispositivos como botones y LEDs, proporcionando interfaces de entrada y salida.
- **Planificador de eventos** para gestionar eventos del sistema y reducir el consumo de energía.

## Funcionalidades Clave

- **Interacción con periféricos** como temporizadores, botones, y UART0.
- **Gestión de eventos** mediante una cola de eventos FIFO y planificador para desencolar y procesar eventos.
- **Reducción del consumo energético** con modos de suspensión y reactivación del procesador.
- **Llamadas al sistema** para activar/desactivar interrupciones IRQ y FIQ, y otras operaciones críticas.
- **Diseño modular** de módulos presentados a través de interfaces definidas en archivos de cabecera (.h).

## Diseño del Sistema

- La implementación del autómata del juego garantiza la adecuada ejecución y coordinación de los diversos componentes del sistema.
- El sistema opera en modos de usuario y supervisor, utilizando llamadas SWI para realizar operaciones de gestión del sistema.
- El enfoque modular permite abstracción de bajo nivel, facilitando la interacción con el programa principal y permitiendo una mayor escalabilidad y mantenimiento del sistema.

