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
| Faros LED delanteros | APROBADO | Tras corregir ambos a rojo `3.3V` y negro `GND`, encienden con brillo continuo. |
| Voltímetro | APROBADO | Lectura estable entre 7.81 V y 7.82 V con alimentación por baterías. |
| ESP-12S, UART E | APROBADO | Con `E_TX -> D19/RX1` y `E_RX -> D18/TX1`, respondió `OK` al comando `AT` a 115200 baudios. |
| Radio Wi-Fi ESP-12S | APROBADO | Consultas de firmware, modo, estado e IP correctas; detectó 19 redes con SSID ocultos y restauró el modo AP original (`2`). |
| Motor 1, BK1 | APROBADO | Rueda frontal derecha; PWM 90; gira hacia adelante y hacia atrás. |
| Motor 2, BK3 | APROBADO | Rueda frontal izquierda; PWM 90; gira hacia adelante. |
| Motor 3, AK1 | APROBADO | Rueda trasera derecha; PWM 90; gira hacia adelante. |
| Motor 4, AK3 | FALLA MECÁNICA | El motor recibe orden, pero la rueda trasera izquierda no transmite giro. Rueda y acople giran juntos sin resistencia; video grabado. |

## Restricción de seguridad

No ejecutar conducción autónoma sobre el piso hasta reparar o reemplazar el acople o motorreductor trasero izquierdo. Las pruebas de motores se realizan con las cuatro ruedas elevadas y parada automática.

## Modo de juego provisional

- El firmware arranca automáticamente después de una cuenta regresiva de ocho segundos.
- Por la avería trasera izquierda, la navegación usa los tres motores sanos; el motor trasero izquierdo queda siempre sin energía.
- La potencia delantera de avance subió de PWM 90 a 125 para ayudar a que ambos motores arranquen juntos; el trasero derecho usa PWM 100 para reducir el desvío.
- Ante un obstáculo confirmado por ultrasonido o IR, hace una reversa limitada a 600 ms y luego explora los lados. Una lectura ultrasónica ausente, por sí sola, mantiene `STOP` y no autoriza la reversa.
- Antes de avanzar exige mediana ultrasónica segura y ambos IR frontales libres.
- Durante cada giro, una sola lectura ultrasónica peligrosa/no fiable o cualquier IR activo produce `STOP`.
- La carga y la lógica de parada se validaron por USB. La prueba elevada del nuevo modo de tres ruedas y la prueba de piso siguen pendientes.

## Hallazgos de cableado

- El HC-SR04 tenía alimentación invertida; se corrigió a `VCC -> 5V` y `GND -> GND`.
- `TRIG -> D30` y `ECHO -> D31` quedaron confirmados.
- El servo estaba dirigido a D12; se corrigió la ruta `Model Y S1 -> D13`.
- El tracker requirió corregir pines y ajustar su potenciómetro azul.
- Para el ESP-12S se seleccionó solamente la ruta UART E; la ruta UART B quedó desconectada.
- La prueba de escaneo usa temporalmente `CWMODE_CUR=3` cuando el ESP está en modo AP y restaura `CWMODE_CUR=2` al terminar.
- El firmware deja servo y motores inactivos mientras el sistema está desarmado.
