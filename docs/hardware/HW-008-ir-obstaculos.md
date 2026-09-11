# HW-008 - Sensores infrarrojos de obstáculos

**Estado:** VERIFICADO_PDF, dos módulos.

## ¿Qué son y para qué sirven?

Son detectores de proximidad simples. Cada uno responde si una superficie refleja suficiente luz infrarroja dentro de su campo.

## ¿Dónde están?

Uno a cada lado del frente superior de PX-32.

## Fenómeno y funcionamiento

Un LED infrarrojo ilumina; un receptor detecta reflexión. Un comparador LM393 contrasta la señal con un umbral fijado por el potenciómetro y produce OUT.

## Componentes importantes

Emisor IR, receptor, LM393, potenciómetro, LEDs indicadores y pines OUT/GND/VCC.

## Pines

| Sensor | OUT | VCC | GND |
|---|---|---|---|
| Izquierdo | D3 | 5V | GND |
| Derecho | D2 | 5V | GND |

## Entrada y salida

Entra radiación reflejada; sale un nivel digital. No entrega una distancia exacta en centímetros.

## Experimento mínimo

Con motores sin energía, imprimir izquierda/derecha por Serial y acercar cartón blanco, tela negra y una mano a igual distancia.

## Errores frecuentes

Tratar OUT como distancia, potenciómetros con umbrales diferentes, confundir izquierda/derecha o calibrar con motores activos.

## Preguntas

1. ¿Por qué el color o acabado cambia la detección?
2. ¿Qué hace el comparador?
3. ¿Qué información se pierde al convertir una señal gradual en 0/1?

## Proyectos

Seguidor de mano y alarma de proximidad.

## Fuente

Manual OSOYOO, pp. 39-43. Imagen: [p. 40](../../assets/osoyoo-manual/pagina-40-conexion-ir-obstaculos.png).
