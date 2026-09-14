# Validación física del robot PX-32

**Fecha:** 2026-09-14  
**Placa:** Arduino Mega 2560, USB `VID 0x2341 / PID 0x0042`  
**Puerto durante las pruebas:** `/dev/cu.usbmodem11401`

## Resultados confirmados

| Componente | Resultado | Evidencia |
|---|---|---|
| Mega 2560 | APROBADO | Detectada por Arduino CLI, compilación y carga correctas. |
| Servo MG90 | APROBADO | Centra y oscila aproximadamente 45 grados hacia cada lado. |
| HC-SR04 | APROBADO | Mediciones repetibles y respuesta ante una mano; se usa mediana de tres. |
| IR de obstáculos izquierdo, D3 | APROBADO | Cambia entre `1 libre` y `0 DETECTA`. |
| IR de obstáculos derecho, D2 | APROBADO | Cambia entre `1 libre` y `0 DETECTA`. |
| Tracker IR1-IR5, A4-A0 | APROBADO | Los cinco bits cambian al desplazar una franja negra sobre fondo blanco. |
| Motor 1, BK1 | APROBADO | Rueda frontal derecha; PWM 90; gira hacia adelante y hacia atrás. |
| Motor 2, BK3 | APROBADO | Rueda frontal izquierda; PWM 90; gira hacia adelante. |
| Motor 3, AK1 | APROBADO | Rueda trasera derecha; PWM 90; gira hacia adelante. |
| Motor 4, AK3 | FALLA MECÁNICA | El motor recibe orden, pero la rueda trasera izquierda no transmite giro. Rueda y acople giran juntos sin resistencia; video grabado. |

## Restricción de seguridad

No ejecutar conducción autónoma sobre el piso hasta reparar o reemplazar el acople o motorreductor trasero izquierdo. Las pruebas de motores se realizan con las cuatro ruedas elevadas y parada automática.

## Hallazgos de cableado

- El HC-SR04 tenía alimentación invertida; se corrigió a `VCC -> 5V` y `GND -> GND`.
- `TRIG -> D30` y `ECHO -> D31` quedaron confirmados.
- El servo estaba dirigido a D12; se corrigió la ruta `Model Y S1 -> D13`.
- El tracker requirió corregir pines y ajustar su potenciómetro azul.
