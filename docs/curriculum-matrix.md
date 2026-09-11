# Matriz curricular de PX-32

`HW-xxx` enlaza al [diccionario de hardware](hardware/README.md). Un guion significa que no se conecta hardware nuevo.

## A. Fundamentos y programación

| Lección | Concepto principal | Hardware | Prerrequisito | Experimento verificable |
|---|---|---|---|---|
| 01 | Robot, sensor, actuador, sistema | PX-32 apagado | Ninguno | Clasificar piezas por función |
| 02 | Inventario y evidencia | HW-001 a HW-020 | 01 | Identificar, contar y fotografiar |
| 03 | Voltaje, corriente, GND, circuito | HW-001, 014-016 | 01 | Representar circuitos abiertos/cerrados sin energía |
| 04 | Microcontrolador, memoria, GPIO | HW-001, HW-002 | 02-03 | Recorrer entrada-proceso-salida en el pinout |
| 05 | IDE, placa, puerto, compilar, cargar | HW-001, HW-020 | 04 | Abrir Blink, verificar y detectar el puerto |
| 06 | `setup`, `loop`, salida digital | HW-001, HW-020 | 05 | Blink a 1000, 500 y 100 ms; SOS |
| 07 | Variables, `int`, `const`, milisegundos | HW-001 | 06 | Cambiar una variable de intervalo |
| 08 | UART USB, `Serial.print` | HW-001, HW-020 | 06-07 | Mensaje “Hola, soy PX-32” y contador |
| 09 | `bool`, comparación, `if/else` | HW-001 | 07-08 | Decidir mensaje según contador |
| 10 | Repetición y `for` | HW-001 | 09 | Producir grupos de destellos contados |
| 11 | Funciones y parámetros | HW-001 | 10 | Crear `parpadear(veces, intervalo)` |

## B. Movimiento

| Lección | Concepto principal | Hardware | Prerrequisito | Experimento verificable |
|---|---|---|---|---|
| 12 | Conversión eléctrica-mecánica | HW-005 | 03 | Observar engranajes con el sistema apagado |
| 13 | Driver de potencia | HW-004, HW-005 | 12 | Trazar ruta señal-potencia |
| 14 | Puente H y polaridad | HW-004 | 13 | Tabla de verdad sin motor energizado |
| 15 | Control de un motor | HW-001, 004, 005 | 11, 14 | Girar un motor con ruedas levantadas |
| 16 | Sentido de giro | HW-004, HW-005 | 15 | Invertir IN1/IN2 por software |
| 17 | PWM y velocidad | HW-004, HW-005 | 16 | Comparar tres duty cycles |
| 18 | Cuatro motores | HW-004-006 | 17 | Identificar cada conector y motor |
| 19 | Rodillos Mecanum a 45° | HW-006, HW-017 | 18 | Predecir fuerzas de una rueda |
| 20 | Vectores y combinación | HW-004-006 | 19 | Hito: seis movimientos con ruedas levantadas y luego en piso |

## C. Infrarrojo

| Lección | Concepto principal | Hardware | Prerrequisito | Experimento verificable |
|---|---|---|---|---|
| 21 | Luz y energía | HW-008 | 03 | Comparar luz visible e IR conceptualmente |
| 22 | Espectro electromagnético | HW-008 | 21 | Ordenar bandas por frecuencia |
| 23 | Radiación infrarroja | HW-008 | 22 | Observar un control remoto con cámara, si funciona |
| 24 | Emisor y receptor | HW-008 | 23 | Identificar ambos componentes en la placa |
| 25 | Reflexión y absorción | HW-008 | 24 | Probar superficies claras/oscuras |
| 26 | Comparador LM393 y umbral | HW-008 | 25 | Observar cambio de OUT y LED |
| 27 | Potenciómetro | HW-008 | 26 | Ajustar umbral con adulto y energía controlada |
| 28 | Entrada digital de un IR | HW-001, HW-008 | 09, 27 | Imprimir `0/1` en Serial |
| 29 | Dos IR y combinación lógica | HW-008 x2 | 28 | Tabla izquierda/derecha |
| 30 | Decisión de seguimiento | HW-004-006, 008 | 20, 29 | Hito: seguir una mano a baja velocidad |

## D. Seguimiento de línea

| Lección | Concepto principal | Hardware | Prerrequisito | Experimento verificable |
|---|---|---|---|---|
| 31 | Arquitectura del tracker | HW-007 | 25 | Identificar cinco pares ópticos |
| 32 | IR1 a IR5 y orden espacial | HW-007 | 31 | Cubrir un canal a la vez |
| 33 | Calibración de umbral | HW-007 | 27, 32 | Comparar negro/blanco |
| 34 | Cinco lecturas digitales | HW-001, HW-007 | 08, 33 | Mostrar patrón `00100` |
| 35 | Arrays | HW-001, HW-007 | 10, 34 | Recorrer cinco sensores con `for` |
| 36 | Posición estimada de línea | HW-007 | 35 | Convertir patrón en izquierda/centro/derecha |
| 37 | Política `if/else` | HW-004-007 | 20, 36 | Decidir sin mover; imprimir orden |
| 38 | Control en pista | HW-004-007 | 37 | Hito: seguir pista de 20-30 mm y registrar errores |

## E. Ultrasonido y servo

| Lección | Concepto principal | Hardware | Prerrequisito | Experimento verificable |
|---|---|---|---|---|
| 39 | Sonido como onda mecánica | HW-009 | 03 | Modelo con pulsos y ecos |
| 40 | Frecuencia, Hz y período | HW-009 | 39 | Cálculos sencillos de ciclos |
| 41 | Audible vs ultrasonido | HW-009 | 40 | Clasificar frecuencias |
| 42 | Velocidad del sonido y eco | HW-009 | 41 | Medir recorrido de ida y vuelta en papel |
| 43 | Pulso TRIG | HW-001, HW-009 | 06, 42 | Emitir pulso de 10 µs |
| 44 | Pulso ECHO | HW-001, HW-009 | 43 | Medir duración con `pulseIn` |
| 45 | Unidades y distancia/2 | HW-009 | 44 | Convertir microsegundos a centímetros |
| 46 | Lectura Serial de distancia | HW-001, HW-009 | 08, 45 | Medir objetos conocidos |
| 47 | Servo y PWM de control | HW-010 | 17 | Mover a 45°, 90° y 135° |
| 48 | Escaneo espacial | HW-009-010 | 46-47 | Medir derecha, centro e izquierda |
| 49 | Decisión de navegación | HW-004-006, 009-010 | 20, 48 | Hito: evitar un obstáculo a baja velocidad |

## F. Bluetooth

| Lección | Concepto principal | Hardware | Prerrequisito | Experimento verificable |
|---|---|---|---|---|
| 50 | Ondas de radio | HW-011 | 22 | Comparar luz y radio |
| 51 | Comunicación inalámbrica | HW-011 | 50 | Dibujar emisor, mensaje, receptor |
| 52 | Bluetooth y emparejamiento | HW-011 | 51 | Reconocer nombre HC-02 |
| 53 | Módulo HC-02 | HW-002, HW-011 | 02, 52 | Identificar módulo y zócalo apagados |
| 54 | UART y baud rate | HW-001, HW-011 | 08, 53 | Enviar caracteres a velocidad acordada |
| 55 | TX y RX cruzados | HW-001, 002, 011 | 54 | Trazar B_TX→RX1 y B_RX→TX1 |
| 56 | Recibir una letra | HW-011 | 55 | Mostrar carácter recibido |
| 57 | Comandos F/B/L/R/S | HW-004-006, 011 | 20, 56 | Hito: control por cinco comandos |

## G. Wi-Fi e IoT

| Lección | Concepto principal | Hardware | Prerrequisito | Experimento verificable |
|---|---|---|---|---|
| 58 | Wi-Fi vs Bluetooth | HW-003, HW-011 | 52 | Tabla de alcance, red y uso |
| 59 | ESP8266/ESP-12S | HW-002-003 | 58 | Identificar antena y ruta UART |
| 60 | Red y nodo | HW-003 | 59 | Dibujar la red del hogar sin contraseñas |
| 61 | Router y enlace | HW-003 | 60 | Identificar AP y cliente |
| 62 | SSID y credenciales | HW-003 | 61 | Usar valores ficticios; nunca versionar claves |
| 63 | Dirección IP y DHCP | HW-003 | 61 | Leer una IP privada por Serial |
| 64 | Cliente, servidor y UDP | HW-003 | 63 | Enviar un comando en red local |
| 65 | Modo STA | HW-002-003 | 62-64 | Conectar PX-32 al router |
| 66 | Interpretar comandos | HW-003-006 | 57, 65 | Mover por UDP a baja velocidad |
| 67 | Telemetría | HW-003, sensores | 66 | Hito: enviar distancia o estado por Wi-Fi |

## H. Integración

| Lección | Concepto principal | Hardware | Prerrequisito | Experimento verificable |
|---|---|---|---|---|
| 68 | Modos y estados | HW-001 | 57, 67 | Máquina de estados STOP/MANUAL/AUTO |
| 69 | Prioridades de seguridad | HW-004-010 | 49, 68 | Sensor detiene una orden manual |
| 70 | Radar ultrasónico | HW-009-010 | 48 | Barrido con tabla ángulo/distancia |
| 71 | Estacionamiento | HW-004-006, 009 | 49 | Mantener separación objetivo |
| 72 | Laberinto | HW-004-006, 009-010 | 49, 68 | Elegir ruta por mediciones |
| 73 | Línea más obstáculos | HW-004-010 | 38, 49, 69 | Pausar o rodear obstáculo |
| 74 | Telemetría integrada | HW-003, sensores | 67, 73 | Reportar modo, sensores y decisión |
| 75 | Proyecto libre | Según diseño | Nivel 5 | Hito final: diseñar, probar, documentar y presentar |
