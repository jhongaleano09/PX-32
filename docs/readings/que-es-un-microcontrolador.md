# ¿Qué es un microcontrolador?

Un microcontrolador es un computador pequeño dentro de un chip. Integra un procesador, memoria y periféricos capaces de medir señales, contar tiempo y comunicarse.

## Las tres memorias que nos importan

- **Flash:** guarda el programa. Por eso PX-32 puede seguir ejecutándolo después de desconectar el USB.
- **SRAM:** mantiene variables mientras el programa corre. Su contenido se pierde al apagar.
- **EEPROM:** puede conservar pequeños datos sin energía, pero no se escribe infinitamente.

## Los periféricos

Un procesador no observa voltajes directamente a cada instante. Usa periféricos especializados: GPIO para estados digitales, ADC para convertir voltajes, timers para tiempo/PWM y UART para caracteres seriales.

## Código y máquina

Nosotros escribimos C++ de Arduino. El compilador traduce ese texto a instrucciones para el ATmega2560. Al cargar, el programa se almacena en flash. Tras un reset, el microcontrolador comienza de nuevo: Arduino prepara el sistema, ejecuta `setup()` una vez y llama `loop()` repetidamente.

## Una limitación valiosa

La Mega2560 no es un computador de escritorio pequeño. Tiene recursos limitados y no puede entregar corriente de motor por sus pines. Esas limitaciones obligan a diseñar con claridad.
