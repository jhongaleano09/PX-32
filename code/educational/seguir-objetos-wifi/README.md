# PX-32: seguimiento de objetos por Wi-Fi

Firmware para OSOYOO Mega 2560 + ESP-12S. Esta carpeta conserva la versión integrada con F6 Seguir Objeto, a partir de la versión local de la lección 49 y sus ajustes existentes de motores, F4 y F5. La copia de carga `kit_osoyoo_test/px32_wifi_control/px32_wifi_control.ino` debe mantenerse igual a `seguir-objetos-wifi.ino`. La lección 49 conserva sus cambios previos independientes.

## Qué hace el firmware (`seguir-objetos-wifi.ino`)

- Crea el punto de acceso `osoyoo_robot` y abre UDP 8888 en `192.168.4.1`.
- Espera órdenes de la app **OSOYOO WiFi UDP Robot Car Controller** (letras A=avanzar, B=reversa, L/R=giros, E=parar).
- Control tipo "hombre muerto": el carro se mueve mientras la app renueva la orden al mantener el botón presionado y frena 250 ms después de soltarlo; los sensores de proximidad no bloquean el movimiento.
- Usa las cuatro ruedas. La polaridad del motor trasero izquierdo se invierte en software después del mantenimiento del 2026-09-16.
- El servo alterna un minuto de barrido entre 45° y 135° con un minuto quieto y centrado.
- Los giros usan las cuatro ruedas: PWM 110 general y PWM 125 en la trasera izquierda para superar su menor fuerza bajo carga.
- El avance tiene compensación individual por rueda para corregir la tendencia del carro a desviarse hacia la derecha.
- Perfiles desde la app: F1 suave (90 %), F2 normal (100 %), F3 potencia (120 %), F4 autónomo con evasión de obstáculos, F5 **Misión Línea** y F6 **Seguir Objeto**.
- Misión Línea sigue una pista negra sobre fondo claro con los cinco sensores inferiores y frena si los IR o el ultrasónico detectan un obstáculo frontal.
- Seguir Objeto usa los dos IR delanteros calibrados a unos 10 cm: ambos detectan = avance; solo izquierdo/derecho = giro hacia ese lado; ninguno = STOP. El ultrasónico permanece centrado. Para arrancar exige tres lecturas seguras consecutivas entre 8 y 12 cm. Frena a 7 cm o menos y permite reanudar desde 8 cm; entre 7 y 8 cm conserva la condición anterior para evitar oscilación.
- F6 avanza y gira de forma continua con PWM 115 en los cuatro motores, sin pausas periódicas ni compensaciones individuales en este modo. Igual PWM significa igual orden de potencia, no igual corriente, energía ni velocidad física: esas dependen del motor, la carga y la fricción.
- En F6 se toma una lectura ultrasónica cada 60 ms o más, sin detener los motores para medir. Una única lectura ausente, superior a 12 cm o demasiado cercana ordena STOP. La espera por eco tiene un máximo de 30 ms; después se atiende cualquier orden Wi-Fi recibida. Los cambios de lado deben mantenerse 60 ms para cambiar la dirección; durante ese filtro se mantiene el movimiento anterior y se sigue midiendo. Perder ambos IR frena sin esperar el filtro. No busca un objeto perdido ni retrocede automáticamente.

## Recompilar y recargar

```bash
arduino-cli compile --fqbn arduino:avr:mega code/educational/seguir-objetos-wifi
arduino-cli upload -p /dev/cu.usbmodem11401 --fqbn arduino:avr:mega code/educational/seguir-objetos-wifi
```

Librerías necesarias (ya instaladas en `~/Documents/Arduino/libraries`): `WiFiEsp`, `Servo`.
Ejecutar desde la raíz de `genomo_bot`. El puerto detectado durante esta tarea puede cambiar al reconectar el USB; consultar `arduino-cli board list` antes de otra carga.

## Verificación sin hardware

```bash
python3 code/educational/seguir-objetos-wifi/tests/test_follow.py
```

Compila el sketch para Mega y ejecuta el mismo código con sensores, reloj y motores simulados usando `clang++` o `g++`. Comprueba avance continuo sin escrituras de parada durante más de un segundo simulado, PWM 115 igual en los cuatro motores durante avance y giros, mediciones durante movimiento, filtro de dirección, pérdida del objeto, histéresis de frenado, ecos ausentes y fuera de alcance, STOP recibido durante medición y cambios de modo. Una única lectura peligrosa debe detener un robot que ya estaba moviéndose. No abre el puerto USB ni sustituye la prueba física.

## Configuración de la tablet

1. WiFi: conectarse a `osoyoo_robot` (clave definida en el sketch).
2. App: en Settings, destino `192.168.4.1`, puerto `8888`.
3. Mantén presionado un botón para mover el carro. Al soltarlo, la ausencia de órdenes lo frena en un máximo nominal de 250 ms; STOP continúa disponible como parada inmediata.
4. F1, F2 y F3 seleccionan el perfil de potencia y dejan el carro detenido. F4 inicia el modo autónomo.
5. F5 inicia Misión Línea. Coloca el centro del arreglo de sensores sobre una pista negra de 20–30 mm en fondo claro antes de encender las baterías. Si no ve la línea, permanece detenido.
6. F6 inicia Seguir Objeto (mensaje UDP `K`, según la [tabla oficial de OSOYOO](https://osoyoo.com/2020/07/24/use-wifi-udp-app-to-control-robot-car-and-3-dof-arm/)). La caja debe estar a la altura de los sensores y reflejar también el ultrasonido. Si el ultrasónico deja de verla al moverla lateralmente, el carro se detiene aunque uno de los IR siga detectándola.
7. STOP cancela cualquier modo autónomo. Una flecha vuelve al control manual; F1–F3 seleccionan potencia y dejan el carro detenido. F4, F5 y F6 cambian entre sus respectivos modos.

## Primera prueba de Seguir Objeto

1. Mantener las ruedas levantadas sobre un soporte firme, conectar la app y pulsar STOP. Comprobar que ambos IR detectan la caja hasta aproximadamente 10 cm y que el ultrasónico apunta al frente.
2. Pulsar F6 y presentar la caja centrada a 8–9 cm del sensor ultrasónico: las cuatro ruedas deben avanzar de forma continua después de las tres lecturas iniciales. Los módulos pueden estar a distinta profundidad; medir desde cada sensor y mantener encendidas las dos luces IR.
3. Desplazar la caja a izquierda y derecha: debe girar hacia el IR que la detecta, siempre que también exista un eco ultrasónico válido.
4. Retirar la caja: todas las ruedas deben detenerse. Acercarla a 7 cm o menos del ultrasónico: también deben detenerse. Alejarla de nuevo hasta 8–9 cm: puede reanudar después de tres lecturas seguras.
5. Pulsar STOP mientras sigue detectando la caja: debe quedar detenido y salir de F6. Repetir F6 y comprobar que F1 deja el carro detenido y que F4/F5 cambian de modo.
6. Solo después de verificar lo anterior, probar en suelo plano, despejado y con STOP a mano. El frenado a 7 cm es un ajuste inicial, no una distancia garantizada: hay que comprobar inercia y respuesta reales. Si no arranca o gira con esta potencia, registrar el resultado antes de aumentarla.

El usuario confirmó ambos IR calibrados a 10 cm, las cuatro combinaciones esperadas usando una caja y el funcionamiento de la primera versión por impulsos. Los mensajes USB también registraron avance, giros y paradas por pérdida de la caja o cercanía. La versión continua, ajustada a PWM 115 a petición del usuario, todavía necesita prueba física de seguimiento y frenado.

## Verificación serial (9600 baudios)

Arranque esperado:

```
[WiFiEsp] Access point started osoyoo_robot
WIFI LISTO | IP: 192.168.4.1 | puerto: 8888
Esperando la tablet: el carro permanece en STOP
```

Con cada botón debe aparecer `ORDEN WIFI: <letra>` y al soltar `STOP WIFI: ...`.

Resultado completo de la validación del 2026-09-14: `../../../experiments/2026-09-14-validacion-hardware.md`.
