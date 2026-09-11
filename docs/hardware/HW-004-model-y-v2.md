# HW-004 - OSOYOO Model Y V2.0

**Estado:** VERIFICADO_PDF por serigrafía de placa en pp. 13, 15 y 17. La tabla de la p. 15 dice `Model Y v1.0`; ver errata E-002.

## ¿Qué es y para qué sirve?

Es el driver de potencia de cuatro canales. Recibe órdenes pequeñas del Mega y conmuta la corriente que necesitan los cuatro motores. También ofrece conectores de servo, entrada/salida de alimentación y conexión al voltímetro.

## ¿Dónde está?

En el chasis inferior, entre los motores.

## Fenómeno y funcionamiento

Un puente H cambia la dirección de la corriente a través de un motor; las entradas EN permiten modular potencia. La placa contiene dos zonas, M_A y M_B, que controlan pares de canales.

## Componentes importantes

Circuitos de potencia, condensadores, conectores AK1/AK3/BK1/BK3, cabeceras ENA/IN1-IN4/ENB, VIN, VOUT, AOUT/BOUT, S1/S2 y GND/5V.

## Pines de control

| Model Y | Mega2560 | Tipo |
|---|---:|---|
| M_A ENA | D11 | PWM/habilitación |
| M_A IN1-IN4 | D5, D6, D7, D8 | Dirección |
| M_A ENB | D12 | PWM/habilitación |
| M_B ENA | D9 | PWM/habilitación |
| M_B IN1-IN4 | D22, D24, D26, D28 | Dirección |
| M_B ENB | D10 | PWM/habilitación |
| S1 | D13 vía shield | Servo |

Motores: frontal derecho BK1, frontal izquierdo BK3, trasero derecho AK1 y trasero izquierdo AK3.

## Alimentación

El portabaterías entra por VIN y VOUT alimenta el shield según el manual. La topología y límites eléctricos exactos del regulador requieren documentación del fabricante; no experimentar con voltajes distintos.

## Experimento mínimo

Primero, sin energía, trazar una señal IN y una ruta de potencia. La primera prueba activa usa un solo motor, ruedas levantadas y un adulto junto al interruptor.

## Errores frecuentes

Cable de seis pines flojo, halar los conductores en vez del conector, confundir zona A/B, batería baja o ruedas apoyadas en la primera prueba.

## Preguntas

1. ¿Por qué el Mega decide pero el driver entrega la potencia?
2. ¿Qué dos cosas controla un puente H?
3. ¿Por qué el primer ensayo se hace con las ruedas en el aire?

## Proyectos

Todo movimiento de PX-32.

## Fuente

Manual OSOYOO, pp. 7-8, 13-15, 17, 24-25.
