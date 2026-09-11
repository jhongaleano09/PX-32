# Código educativo de PX-32

Cada sketch vive en una carpeta del mismo nombre que su archivo `.ino`, como requiere Arduino IDE. Son programas mínimos del curso: se leen y predicen antes de cargarse. Las constantes de pines coinciden con el [mapa canónico](../../docs/reference/mapa-conexiones-robot.md).

| Lección | Sketch | Idea aislada |
|---:|---|---|
| 06 | [06-primer-programa-blink/06-primer-programa-blink.ino](06-primer-programa-blink/06-primer-programa-blink.ino) | setup, loop, salida digital y delay |
| 07 | [07-variables-para-representar-tiempo/07-variables-para-representar-tiempo.ino](07-variables-para-representar-tiempo/07-variables-para-representar-tiempo.ino) | variable, const, int, asignación y milisegundo |
| 08 | [08-px-32-aprende-a-hablarnos/08-px-32-aprende-a-hablarnos.ino](08-px-32-aprende-a-hablarnos/08-px-32-aprende-a-hablarnos.ino) | Serial, UART, baud rate, print y observabilidad |
| 09 | [09-decisiones-con-if-y-else/09-decisiones-con-if-y-else.ino](09-decisiones-con-if-y-else/09-decisiones-con-if-y-else.ino) | bool, comparación, condición y rama |
| 10 | [10-repeticiones-contadas-con-for/10-repeticiones-contadas-con-for.ino](10-repeticiones-contadas-con-for/10-repeticiones-contadas-con-for.ino) | bucle, contador, condición y actualización |
| 11 | [11-funciones-ensenar-una-accion-reutilizable/11-funciones-ensenar-una-accion-reutilizable.ino](11-funciones-ensenar-una-accion-reutilizable/11-funciones-ensenar-una-accion-reutilizable.ino) | función, parámetro, argumento y retorno |
| 15 | [15-primera-prueba-de-un-motor/15-primera-prueba-de-un-motor.ino](15-primera-prueba-de-un-motor/15-primera-prueba-de-un-motor.ino) | salida digital, habilitación y parada física |
| 16 | [16-invertir-el-sentido-por-software/16-invertir-el-sentido-por-software.ino](16-invertir-el-sentido-por-software/16-invertir-el-sentido-por-software.ino) | dirección, inversión lógica e invariante de seguridad |
| 17 | [17-pwm-regular-energia-en-el-tiempo/17-pwm-regular-energia-en-el-tiempo.ino](17-pwm-regular-energia-en-el-tiempo/17-pwm-regular-energia-en-el-tiempo.ino) | PWM, ciclo de trabajo, frecuencia y velocidad media |
| 18 | [18-cuatro-motores-cuatro-identidades/18-cuatro-motores-cuatro-identidades.ino](18-cuatro-motores-cuatro-identidades/18-cuatro-motores-cuatro-identidades.ino) | motor frontal/trasero, izquierdo/derecho y prueba aislada |
| 20 | [20-vectores-para-mover-px-32/20-vectores-para-mover-px-32.ino](20-vectores-para-mover-px-32/20-vectores-para-mover-px-32.ino) | vector, suma, traslación, rotación y STOP |
| 28 | [28-leer-un-sensor-ir-por-un-pin-digital/28-leer-un-sensor-ir-por-un-pin-digital.ino](28-leer-un-sensor-ir-por-un-pin-digital/28-leer-un-sensor-ir-por-un-pin-digital.ino) | INPUT, digitalRead, HIGH y LOW |
| 29 | [29-dos-sensores-cuatro-situaciones/29-dos-sensores-cuatro-situaciones.ino](29-dos-sensores-cuatro-situaciones/29-dos-sensores-cuatro-situaciones.ino) | AND, OR, tabla de verdad y combinación |
| 30 | [30-seguir-una-mano-con-prudencia/30-seguir-una-mano-con-prudencia.ino](30-seguir-una-mano-con-prudencia/30-seguir-una-mano-con-prudencia.ino) | política de control, zona muerta y parada |
| 34 | [34-leer-cinco-sensores-sin-perderse/34-leer-cinco-sensores-sin-perderse.ino](34-leer-cinco-sensores-sin-perderse/34-leer-cinco-sensores-sin-perderse.ino) | muestreo, patrón y formato |
| 35 | [35-arrays-cinco-datos-bajo-un-nombre/35-arrays-cinco-datos-bajo-un-nombre.ino](35-arrays-cinco-datos-bajo-un-nombre/35-arrays-cinco-datos-bajo-un-nombre.ino) | array, índice, longitud y límite |
| 36 | [36-estimar-donde-esta-la-linea/36-estimar-donde-esta-la-linea.ino](36-estimar-donde-esta-la-linea/36-estimar-donde-esta-la-linea.ino) | posición, peso, promedio y caso perdido |
| 37 | [37-de-la-medicion-a-la-orden/37-de-la-medicion-a-la-orden.ino](37-de-la-medicion-a-la-orden/37-de-la-medicion-a-la-orden.ino) | política if/else, decisión y separación de responsabilidades |
| 38 | [38-hito-seguir-una-linea/38-hito-seguir-una-linea.ino](38-hito-seguir-una-linea/38-hito-seguir-una-linea.ino) | realimentación, corrección y velocidad de prueba |
| 43 | [43-trig-enviar-un-pulso-breve/43-trig-enviar-un-pulso-breve.ino](43-trig-enviar-un-pulso-breve/43-trig-enviar-un-pulso-breve.ino) | pulso, microsegundo, OUTPUT y digitalWrite |
| 44 | [44-echo-medir-una-duracion/44-echo-medir-una-duracion.ino](44-echo-medir-una-duracion/44-echo-medir-una-duracion.ino) | pulseIn, temporización y timeout |
| 45 | [45-de-microsegundos-a-centimetros/45-de-microsegundos-a-centimetros.ino](45-de-microsegundos-a-centimetros/45-de-microsegundos-a-centimetros.ino) | unidad, conversión, constante y distancia |
| 46 | [46-medir-objetos-conocidos/46-medir-objetos-conocidos.ino](46-medir-objetos-conocidos/46-medir-objetos-conocidos.ino) | precisión, exactitud, repetición y mediana |
| 47 | [47-un-servo-apunta-el-sensor/47-un-servo-apunta-el-sensor.ino](47-un-servo-apunta-el-sensor/47-un-servo-apunta-el-sensor.ino) | servo, ángulo, posición y señal de control |
| 48 | [48-escaneo-espacial/48-escaneo-espacial.ino](48-escaneo-espacial/48-escaneo-espacial.ino) | barrido, muestra, ángulo y mapa polar |
| 49 | [49-evitar-obstaculos/49-evitar-obstaculos.ino](49-evitar-obstaculos/49-evitar-obstaculos.ino) | umbral de seguridad, elección y maniobra |
| 54 | [54-uart-hablar-por-turnos-y-a-la-misma-velocidad/54-uart-hablar-por-turnos-y-a-la-misma-velocidad.ino](54-uart-hablar-por-turnos-y-a-la-misma-velocidad/54-uart-hablar-por-turnos-y-a-la-misma-velocidad.ino) | UART, trama, baud rate, TX y RX |
| 55 | [55-tx-y-rx-se-cruzan/55-tx-y-rx-se-cruzan.ino](55-tx-y-rx-se-cruzan/55-tx-y-rx-se-cruzan.ino) | transmisión, recepción, RX1 y TX1 |
| 56 | [56-recibir-una-letra/56-recibir-una-letra.ino](56-recibir-una-letra/56-recibir-una-letra.ino) | byte, carácter, available y read |
| 57 | [57-control-bluetooth-con-parada-dominante/57-control-bluetooth-con-parada-dominante.ino](57-control-bluetooth-con-parada-dominante/57-control-bluetooth-con-parada-dominante.ino) | comando, despacho, watchdog y STOP |
| 63 | [63-direcciones-ip-y-dhcp/63-direcciones-ip-y-dhcp.ino](63-direcciones-ip-y-dhcp/63-direcciones-ip-y-dhcp.ino) | IP privada, DHCP, puerto y dirección |
| 64 | [64-cliente-servidor-y-udp/64-cliente-servidor-y-udp.ino](64-cliente-servidor-y-udp/64-cliente-servidor-y-udp.ino) | cliente, servidor, datagrama, UDP y puerto |
| 65 | [65-conectar-en-modo-estacion/65-conectar-en-modo-estacion.ino](65-conectar-en-modo-estacion/65-conectar-en-modo-estacion.ino) | modo STA, asociación, timeout y reintento |
| 66 | [66-comandos-wi-fi-seguros/66-comandos-wi-fi-seguros.ino](66-comandos-wi-fi-seguros/66-comandos-wi-fi-seguros.ino) | validación, comando, origen y caducidad |
| 67 | [67-telemetria-el-robot-informa/67-telemetria-el-robot-informa.ino](67-telemetria-el-robot-informa/67-telemetria-el-robot-informa.ino) | telemetría, estado, muestreo y tasa |
| 68 | [68-pensar-en-modos-y-estados/68-pensar-en-modos-y-estados.ino](68-pensar-en-modos-y-estados/68-pensar-en-modos-y-estados.ino) | estado, transición, evento y máquina de estados |
| 69 | [69-la-seguridad-tiene-prioridad/69-la-seguridad-tiene-prioridad.ino](69-la-seguridad-tiene-prioridad/69-la-seguridad-tiene-prioridad.ino) | prioridad, interbloqueo, fallo seguro y arbitraje |
| 70 | [70-radar-ultrasonico/70-radar-ultrasonico.ino](70-radar-ultrasonico/70-radar-ultrasonico.ino) | radar como analogía, barrido, tabla y visualización |
| 71 | [71-estacionamiento-por-distancia/71-estacionamiento-por-distancia.ino](71-estacionamiento-por-distancia/71-estacionamiento-por-distancia.ino) | consigna, error, tolerancia y control proporcional simple |
| 72 | [72-navegar-un-laberinto/72-navegar-un-laberinto.ino](72-navegar-un-laberinto/72-navegar-un-laberinto.ino) | estrategia, heurística, memoria y callejón sin salida |
| 73 | [73-linea-con-obstaculos/73-linea-con-obstaculos.ino](73-linea-con-obstaculos/73-linea-con-obstaculos.ino) | fusión de sensores, prioridad y comportamiento compuesto |
| 74 | [74-telemetria-integrada/74-telemetria-integrada.ino](74-telemetria-integrada/74-telemetria-integrada.ino) | registro, marca de tiempo, modo y decisión |
| 75 | [75-proyecto-final-tu-propio-px-32/75-proyecto-final-tu-propio-px-32.ino](75-proyecto-final-tu-propio-px-32/75-proyecto-final-tu-propio-px-32.ino) | requisito, prototipo, prueba, evidencia e iteración |

Los sketches Wi-Fi no contienen credenciales. Bluetooth y ESP8266 comparten `Serial1`; el adulto confirma que solo una ruta B/E esté activa. Los ejemplos de integración dejan `detener()` deliberadamente seguro e incompleto cuando copiar movimiento sin la verificación de la lección sería peligroso.
