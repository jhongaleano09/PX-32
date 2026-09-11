# HW-013 - Luces LED delanteras

**Estado:** VERIFICADO_PDF, dos unidades; no se documenta resistencia o driver separado.

## ¿Qué son y para qué sirven?

Son actuadores luminosos instalados como faros. Convierten corriente eléctrica en luz visible.

## ¿Dónde están?

En la placa transversal frontal.

## Fenómeno y funcionamiento

En un diodo emisor de luz, electrones y huecos se recombinan en un semiconductor y liberan energía como fotones. Un LED tiene polaridad.

## Conexiones

| Cable | Shield | Precaución |
|---|---|---|
| Rojo, VCC | 3.3V o 5V según manual | Cambia el brillo |
| Negro, GND | GND | No invertir |

El manual los conecta como luces siempre encendidas, no a GPIO. `STATUS: PENDIENTE_DE_VERIFICAR` si el conjunto incluye resistencia interna.

## Experimento mínimo

Primero solo observar polaridad y ruta con el sistema apagado. No usar estos faros para la primera práctica Blink porque el manual no documenta control individual por GPIO.

## Errores frecuentes

Confundir VCC con señal, invertir polaridad o conectar un LED desnudo sin resistencia basándose en este módulo ensamblado.

## Preguntas

1. ¿Por qué importa la polaridad?
2. ¿Qué cambia entre 3.3 V y 5 V según OSOYOO?
3. ¿Por qué un módulo LED puede diferir de un LED suelto?

## Proyectos

Iluminación de PX-32; un control programable requerirá verificar el módulo antes de diseñarlo.

## Fuente

Manual OSOYOO, pp. 12, 15-16.
