# HW-002 - OSOYOO UART WiFi Shield V1.3

**Estado:** VERIFICADO_PDF.

## ¿Qué es y para qué sirve?

Es una placa que se monta encima de la Mega2560 y organiza conexiones de sensores, motores, Bluetooth y Wi-Fi. No reemplaza al Mega: amplía y distribuye sus pines.

## ¿Dónde está en PX-32?

Encajada sobre HW-001 en el chasis superior.

## Cómo funciona

Las pistas de cobre llevan alimentación y señales entre la Mega, conectores de tres filas, el ESP12/S, el zócalo Bluetooth y cabeceras UART. Algunos puentes físicos seleccionan rutas de comunicación.

## Partes importantes

Módulo ESP12/S, zócalo BLE/HC-02, grupos S/V/GND, cabeceras B_TX/B_RX y E_TX/E_RX, entradas VIN/GND e interruptor.

## Pines y conexiones

| Zona | Conexión | Uso |
|---|---|---|
| D2-D13 | S/V/GND | Sensores, motor driver y servo |
| A0-A4 | S/V/GND | Tracker de cinco canales |
| B_TX/B_RX | D19/D18 | Bluetooth por Serial1 |
| E_TX/E_RX | D19/D18 | ESP por Serial1 |
| VIN/GND | VOUT Model Y | Alimentación del conjunto |

Solo se usa una ruta Serial1 según la configuración indicada en la lección correspondiente.

## Alimentación

El manual conecta VOUT del Model Y a VIN del shield. No cambiar puentes ni conexiones con el sistema energizado.

## Entrada, salida y lenguaje

Distribuye digital, analógico y UART; también lleva alimentación. La dirección real de cada señal depende del módulo conectado.

## Experimento mínimo

Con todo apagado, seguir visualmente una fila S/V/GND desde el shield hasta un sensor y dibujarla. No insertar ni retirar el shield con energía.

## Errores frecuentes

Desalinear pines al apilar, confundir S con V, usar a la vez B_UART y ESP_UART, o asumir que todos los grupos rojos/amarillos tienen la misma función sin leer la serigrafía.

## Preguntas

1. ¿Por qué un shield puede facilitar conexiones sin ser el cerebro?
2. ¿Qué comparten todos los módulos conectados a GND?
3. ¿Qué pasaría si TX no llega a una entrada RX?

## Proyectos

Todos los proyectos montados de PX-32.

## Fuente

Manual OSOYOO, pp. 9, 13, 15-18, 24, 29, 35, 40, 45, 52-53.
