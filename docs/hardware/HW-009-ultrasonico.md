# HW-009 - Sensor ultrasónico

**Estado:** VERIFICADO_PDF; el módulo ilustrado tiene disposición tipo HC-SR04, pero el manual lo nombra genéricamente “Ultrasonic module”.

## ¿Qué es y para qué sirve?

Mide distancia enviando un sonido demasiado agudo para nuestro oído y cronometrando su eco.

## ¿Dónde está?

En el frente, sobre un soporte movido por el servo.

## Fenómeno y funcionamiento

Un pulso en TRIG inicia una ráfaga ultrasónica. El transmisor T emite; el receptor R escucha. ECHO permanece activo durante un tiempo relacionado con el viaje de ida y vuelta. La distancia es velocidad por tiempo, dividida entre dos.

## Componentes importantes

Transductor T, transductor R, circuito temporizador y pines VCC/TRIG/ECHO/GND.

## Pines

| Ultrasónico | Mega/shield | Tipo |
|---|---|---|
| VCC | 5V | Alimentación |
| TRIG | D30 | Salida desde Mega |
| ECHO | D31 | Entrada a Mega |
| GND | GND | Referencia |

## Experimento mínimo

Con motores sin energía, medir una caja situada aproximadamente a 10, 20 y 30 cm e imprimir resultados. Comparar repetición y error; no esperar exactitud perfecta.

## Errores frecuentes

TRIG/ECHO invertidos, objeto inclinado que desvía el eco, objeto blando que absorbe sonido, timeout interpretado como 0 cm o dividir incorrectamente el viaje doble.

## Preguntas

1. ¿Por qué dividimos entre dos?
2. ¿Qué ocurre si el eco no regresa?
3. ¿Por qué una superficie inclinada puede “desaparecer”?

## Proyectos

Medidor, radar, estacionamiento, evasión y laberinto.

## Fuente

Manual OSOYOO, pp. 26-33. Imagen: [p. 29](../../assets/osoyoo-manual/pagina-29-conexion-ultrasonico.png).
