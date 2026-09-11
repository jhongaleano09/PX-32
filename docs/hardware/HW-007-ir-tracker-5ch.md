# HW-007 - OSOYOO 5-Channel IR Tracker

**Estado:** VERIFICADO_PDF. El texto de pp. 17 y 34 contiene duplicaciones; el diagrama de pp. 18 y 35 define el mapa canónico.

## ¿Qué es y para qué sirve?

Es una fila de cinco sensores reflectivos que permite saber dónde está una línea respecto al centro de PX-32.

## ¿Dónde está?

En el frente inferior, mirando al suelo.

## Fenómeno y funcionamiento

Cada canal emite infrarrojo y detecta cuánto regresa. Superficies distintas reflejan cantidades distintas. El circuito compara la señal con un umbral ajustable y entrega cinco estados.

## Componentes importantes

Cinco pares emisor/receptor, indicadores LED, comparadores/circuito de acondicionamiento, potenciómetro, IR1-IR5, VCC y GND.

## Pines

| Tracker | Mega/shield | Posición lógica |
|---|---|---|
| IR1 | A4 | Extremo 1 |
| IR2 | A3 | Interior 1 |
| IR3 | A2 | Centro |
| IR4 | A1 | Interior 2 |
| IR5 | A0 | Extremo 2 |
| VCC | 5V | Alimentación |
| GND | GND | Referencia |

Antes de usar izquierda/derecha se confirmará la orientación física montada de PX-32.

## Entrada y salida

Entra luz reflejada; salen cinco señales digitales que la Mega puede leer también por pines A0-A4 usados como entradas digitales.

## Experimento mínimo

Con motores desconectados, imprimir cinco bits en Serial y mover una tira negra bajo un canal a la vez.

## Errores frecuentes

Seguir el texto OCR defectuoso, invertir el conector de siete pines, altura incorrecta, luz ambiente intensa o calibración pobre.

## Preguntas

1. ¿Por qué cinco canales dan más información que uno?
2. ¿Qué patrón esperarías con la línea centrada?
3. ¿Por qué hace falta calibrar para el piso real?

## Proyectos

Seguidor de línea y línea con obstáculos.

## Fuente

Manual OSOYOO, pp. 17-18 y 34-38. Imagen canónica: [p. 18](../../assets/osoyoo-manual/pagina-18-pinout-tracker-correcto.png).
