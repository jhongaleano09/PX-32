# HW-012 - Voltímetro LED de tres dígitos

**Estado:** VERIFICADO_PDF; rango y precisión exactos pendientes.

## ¿Qué es y para qué sirve?

Muestra una estimación del voltaje de alimentación. Ayuda a relacionar el estado de las baterías con el comportamiento de PX-32.

## ¿Dónde está?

Montado cerca del borde del chasis inferior/superior según las fotografías, conectado al Model Y.

## Fenómeno y funcionamiento

Un circuito convierte un voltaje analógico en un número y enciende segmentos LED para mostrarlo.

## Pines

| Voltímetro | Model Y según tabla p. 15 | Función |
|---|---|---|
| GND | GND | Referencia |
| VCC | 5V | Alimentación del display |
| VT | S | Señal medida |

## Alimentación

No usar fuera del cableado del kit hasta verificar rango, polaridad y modelo impresos físicamente.

## Entrada y salida

Entra un voltaje; sale una lectura visual aproximada. No envía datos a la Mega en la configuración documentada.

## Experimento mínimo

Con supervisión adulta, registrar la lectura antes y después de una prueba corta de motores. No modificar cables energizados.

## Errores frecuentes

Confundir lectura con porcentaje exacto de carga, invertir polaridad o asumir precisión de laboratorio.

## Preguntas

1. ¿Por qué el voltaje puede caer cuando arrancan motores?
2. ¿Una pantalla con más dígitos siempre es más exacta?
3. ¿Qué diferencia hay entre medir y alimentar?

## Proyectos

Conversación sobre variación de la alimentación y velocímetro conceptual.

## Fuente

Manual OSOYOO, pp. 8, 14-15 y listas de partes.
