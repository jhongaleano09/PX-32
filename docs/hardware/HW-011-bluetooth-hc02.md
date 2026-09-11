# HW-011 - Bluetooth HC-02

**Estado:** VERIFICADO_PDF como HC-02; pines KEY/EN/STATE dependen de la variante y solo aparecen en el procedimiento opcional de cambio de nombre.

## ¿Qué es y para qué sirve?

Es un módulo de radio de corto alcance que permite enviar comandos desde un teléfono a PX-32 sin cable.

## ¿Dónde está?

Se inserta en el zócalo Bluetooth de seis pines del UART WiFi Shield.

## Fenómeno y funcionamiento

Usa ondas de radio y un protocolo Bluetooth. El módulo maneja el enlace inalámbrico; hacia la Mega traduce los datos a caracteres por UART.

## Partes importantes

Antena impresa, circuito de radio, LED de estado y pines de UART/alimentación. La placa exacta debe fotografiarse por ambos lados.

## Pines y conexiones normales del kit

| Shield | Mega2560 | Sentido |
|---|---|---|
| B_TX | D19/RX1 | Módulo -> Mega |
| B_RX | D18/TX1 | Mega -> módulo |

El manual también muestra D4/D5 con `SoftwareSerial` solo para reconfigurar el nombre mediante comandos AT; no es el cableado normal del robot.

## Alimentación

Insertar únicamente con PX-32 apagado. El zócalo del shield ofrece la alimentación prevista. No deducir tolerancia de 5 V de los pines lógicos a partir de la alimentación del módulo.

## Experimento mínimo

Recibir un solo carácter y mostrarlo por Serial USB. El movimiento se añade después de validar F/B/L/R/S con los motores deshabilitados.

## Errores frecuentes

TX con TX, baud rate incorrecto, módulo no emparejado, confundir el cableado AT con el normal o intentar usar ESP y Bluetooth simultáneamente en Serial1.

## Preguntas

1. ¿Por qué TX debe llegar a RX?
2. ¿Qué diferencia hay entre emparejar y enviar un comando?
3. ¿Por qué primero mostramos la letra antes de mover ruedas?

## Proyectos

Control Bluetooth y mando físico futuro.

## Fuente

Manual OSOYOO, pp. 44-51. Imagen: [p. 45](../../assets/osoyoo-manual/pagina-45-conexion-bluetooth.png).
