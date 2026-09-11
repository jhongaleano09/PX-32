# Pinout relevante de la Mega2560 en PX-32

Esta no es una copia de todos los 70 pines posibles. Es el mapa de los pines usados por el kit y los primeros conceptos del curso.

## Capacidades de referencia

La Arduino Mega 2560 oficial tiene 54 pines digitales, 16 entradas analógicas, 4 UART de hardware y trabaja con el ATmega2560. La placa OSOYOO se presenta como compatible. Para límites absolutos y revisión eléctrica se debe consultar documentación del fabricante de la placa exacta.

## Mapa canónico de PX-32

| Pin Mega | Capacidad | Uso OSOYOO/PX-32 | Reservado desde |
|---|---|---|---|
| D2 | Digital, interrupción | OUT sensor IR derecho | Bloque IR |
| D3 | Digital/PWM, interrupción | OUT sensor IR izquierdo | Bloque IR |
| D5 | Digital/PWM | M_A IN1 | Movimiento |
| D6 | Digital/PWM | M_A IN2 | Movimiento |
| D7 | Digital/PWM | M_A IN3 | Movimiento |
| D8 | Digital/PWM | M_A IN4 | Movimiento |
| D9 | Digital/PWM | M_B ENA | Movimiento |
| D10 | Digital/PWM | M_B ENB | Movimiento |
| D11 | Digital/PWM | M_A ENA | Movimiento |
| D12 | Digital/PWM | M_A ENB | Movimiento |
| D13 | Digital/PWM, LED integrado | Servo S1 y LED integrado | Primer programa/servo |
| D18/TX1 | UART Serial1 TX | B_RX o E_RX | Comunicación |
| D19/RX1 | UART Serial1 RX | B_TX o E_TX | Comunicación |
| D20/SDA | I2C datos | Libre en manual | Expansiones |
| D21/SCL | I2C reloj | Libre en manual | Expansiones |
| D22, D24, D26, D28 | Digital | M_B IN1-IN4 | Movimiento |
| D30 | Digital | TRIG ultrasónico | Ultrasonido |
| D31 | Digital | ECHO ultrasónico | Ultrasonido |
| A0 | ADC/digital | IR5 tracker | Línea |
| A1 | ADC/digital | IR4 tracker | Línea |
| A2 | ADC/digital | IR3 tracker | Línea |
| A3 | ADC/digital | IR2 tracker | Línea |
| A4 | ADC/digital | IR1 tracker | Línea |
| 5V | Alimentación | Módulos de 5 V documentados | Siempre |
| 3V3 | Alimentación | Salida disponible; LEDs según manual | Siempre |
| GND | Referencia | Retorno común | Siempre |
| VIN | Alimentación de entrada | Ruta mediante shield/Model Y | Potencia |

## Conflicto educativo importante: D13

El ejemplo Blink usa `LED_BUILTIN`, que en Mega2560 corresponde a D13. En PX-32 ensamblado, D13 también se enruta al servo S1. Por eso Blink se realiza con la placa separada del sistema de potencia o con el servo y baterías desconectados por un adulto y todo apagado antes del cambio.

## UART de hardware

| Objeto Arduino | RX | TX | Uso en PX-32 |
|---|---:|---:|---|
| `Serial` | D0 | D1 | USB/monitor durante el curso |
| `Serial1` | D19 | D18 | Bluetooth o ESP mediante shield |
| `Serial2` | D17 | D16 | No asignado por el manual |
| `Serial3` | D15 | D14 | No asignado por el manual |

## Fuentes

- Manual OSOYOO, pp. 13, 17-18, 29, 40, 45 y 53.
- [Arduino Mega 2560 Rev3](https://docs.arduino.cc/hardware/mega-2560/).
- [Pinout oficial en PDF](https://docs.arduino.cc/resources/pinouts/A000067-full-pinout.pdf).
