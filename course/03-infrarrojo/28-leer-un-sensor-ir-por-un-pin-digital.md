# Lección 28 — Leer un sensor IR por un pin digital

## Un pin que escucha

Hasta ahora, el veredicto del sensor vivía en un LED: encendido o apagado, y nada más. Pero la Mega 2560 no tiene ojos para mirar LEDs. Necesita recibir ese veredicto por un cable, en su idioma: voltajes.

El camino ya está tendido. El pin OUT del sensor izquierdo termina en el pin **D3** de la Mega a través del shield (lo verificaste en la Lección 24): cuando el LM393 cambia de veredicto, el voltaje del pin D3 cambia entre dos niveles, HIGH y LOW. Lo nuevo de hoy es enseñarle al programa a escuchar.

Para escuchar, un pin se configura distinto que para empujar. En el Blink y en los motores usaste `pinMode(..., OUTPUT)`: el pin empuja, decide su propio voltaje. Hoy usas `pinMode(..., INPUT)`: el pin no decide nada, obedece el voltaje que le llega por el cable y nada más. Y la orden para preguntarle cómo está es `digitalRead(pin)`, que contesta exactamente dos cosas posibles: `HIGH` (nivel alto, en esta placa cercano a 5 V) o `LOW` (nivel bajo, cercano a GND). Dos palabras que conoces desde la Lección 03.

Si vienes de Scratch, esto te va a sonar: el bloque "¿presionando la barra espaciadora?" no dibuja nada ni mueve nada; solo contesta verdadero o falso, y un "si… entonces" hace el resto. `digitalRead()` es ese bloque: pregunta el estado del pin; `if` (Lección 09) decide con la respuesta.

Queda un misterio técnico, y es el más interesante del día: ¿cuál de los dos valores significa "detecté algo"? En muchos módulos con LM393, la salida es activa-baja: detectar entrega LOW y el aire libre entrega HIGH. Pero "muchos módulos" no es una prueba, y este curso no reparte hechos sin evidencia. Hoy vas a medirlo con tu propio sensor y a escribir la respuesta en tu cuaderno. Esa nota será la clave de las Lecciones 29 y 30.

## Lo que necesitas

- PX-32 con ambos sensores conectados y calibrados a la ventana de 10/15 cm (Lección 27).
- Tu mano o el cartón blanco y la regla.
- Computador con Arduino IDE 2, cable USB de datos.
- El sketch [28-leer-un-sensor-ir-por-un-pin-digital.ino](../../code/educational/28-leer-un-sensor-ir-por-un-pin-digital/28-leer-un-sensor-ir-por-un-pin-digital.ino).
- Tu cuaderno, abierto en una página nueva titulada "Lecturas de D3".
- Un adulto para el USB.

Estado inicial: PX-32 apagado, sin baterías. Los motores no participan: el sketch de hoy no menciona un solo pin de motor.

🟡 El adulto conecta el USB cuando toque y lo retira al cierre. La clase no tiene movimiento.

## Lee el programa antes de cargarlo

1. 🟢 Abre el `.ino` y recórrelo línea por línea. Debe ser idéntico a este bloque:

```cpp
// Curso PX-32 - Leccion 28: leer el sensor IR izquierdo en D3.

const byte SENSOR_IR_IZQUIERDO = 3;

void setup() {
  pinMode(SENSOR_IR_IZQUIERDO, INPUT);
  Serial.begin(9600);
}

void loop() {
  int lectura = digitalRead(SENSOR_IR_IZQUIERDO);
  Serial.println(lectura);
  delay(200);
}
```

2. 🟢 **`const byte SENSOR_IR_IZQUIERDO = 3;`** le pone nombre al número del pin, como hiciste con `LIMITE` en la Lección 09. `byte` alcanza para guardar un número pequeño como 3, y `const` recuerda al compilador que no va a cambiar. Cuando leas `SENSOR_IR_IZQUIERDO`, piensa "el cable que viene del sensor izquierdo".

3. 🟢 **`pinMode(SENSOR_IR_IZQUIERDO, INPUT);`** configura D3 como entrada: el pin escuchará el voltaje que trae el cable OUT del sensor, en vez de imponer el suyo. Va en `setup()` porque basta decirlo una vez.

4. 🟢 **`int lectura = digitalRead(SENSOR_IR_IZQUIERDO);`** es el corazón de la clase: pregunta el estado actual del pin y guarda la respuesta (`HIGH` o `LOW`) en una variable, lista para usar. Ocurre una vez por vuelta de `loop()`.

5. 🟢 **`Serial.println(lectura);`** imprime esa respuesta en su propia línea. Cuando `println` recibe `HIGH` imprime `1` y con `LOW` imprime `0`: son las mismas cosas con otro disfraz (Lecciones 08 y 09).

6. 🟢 **`delay(200);`** frena la vuelta un quinto de segundo para que el monitor muestre unas cinco líneas por segundo: un ritmo que tus ojos pueden leer. Sin esta pausa el monitor se llena de números a toda velocidad.

7. 🟢 **Predice antes de cargar.** Escribe en el cuaderno: "Con la sala despejada, el monitor mostrará ___" (¿0 o 1?) y "Con mi mano a 10 cm, mostrará ___". Son dos apuestas; abajo las cobras o las corriges.

## El experimento: averigua qué significa cada número

8. 🟡 **Carga y abre el oído.** El adulto conecta el USB. Elige la Mega y su puerto, verifica y sube el sketch. Abre el monitor serie a 9600 baudios. Deberías ver una columna estable con el mismo número, una y otra vez.

9. 🟢 **Situación 1: aire libre.** Aléjate del robot, deja el frente del sensor sin nada. Anota el número que se repite. Ese es el estado "no detecta" de tu módulo.

10. 🟢 **Situación 2: mano a 10 cm.** Coloca tu mano abierta a 10 cm del sensor izquierdo, medidos con la regla. La columna debería cambiar al otro valor. Retírala: regresa. Acércala: cambia. Repite el ciclo tres veces: los cambios deben ser limpios y repetibles.

11. 🟢 **Escribe tu ley.** En el cuaderno, con fecha: "En mi sensor, detectar = ___ y aire libre = ___". La respuesta más frecuente en estos módulos es detectar = 0 y aire libre = 1 (salida activa-baja), pero lo que manda es tu medición. Esta nota viaja contigo a las próximas dos lecciones; sin ella, los programas del hito leerán al revés.

12. 🟢 **Un solo cambio: la dirección.** Cambia únicamente `= 3` por `= 2` en la línea de la constante. Antes de subir, predice: ¿qué sensor escucharás ahora? Sube y comprueba tapando primero un sensor y luego el otro con la mano: la columna solo debe reaccionar al derecho. Moraleja: el número del código y el cable deciden juntos a quién escucha la Mega. Deja el sketch de vuelta en 3.

13. 🟢 **Un solo cambio: el ritmo.** Cambia solo `delay(200)` por `delay(50)`. Predice cuántas líneas por segundo aparecerán (cuenta durante cinco segundos y divide). ¿El robot se volvió más sensible? No: escucha más seguido, que es distinto. Vuelve a 200 para leer tranquilo.

14. 🟢 **El vocabulario completo, junto.** Recuerda el vocabulario de la clase: el módulo entrega en OUT un nivel **digital** de dos posibles gracias al comparador (Lección 26); la Mega lo lee con `digitalRead`; `HIGH`/`LOW` son los nombres del voltaje alto y bajo; `1`/`0` son sus disfraces impresos.

15. 🟡 **Cierre.** Cierra el monitor, el adulto retira el USB. El robot queda apagado, calibración intacta.

El experimento está completo cuando tu cuaderno tiene la ley del paso 11 comprobada tres veces, y puedes explicar por qué `digitalRead` es el bloque de preguntas de Scratch convertido a C++.

> **[PENDIENTE VISUAL]**
> - **Tipo:** captura del monitor serie junto a fotografía del montaje.
> - **Objetivo:** mostrar el contraste entre las dos lecturas y dónde ocurren físicamente.
> - **Descripción:** imagen dividida: a la izquierda, la mano a 10 cm del sensor izquierdo con la regla visible; a la derecha, el monitor serie mostrando una columna de 1 que cambia a 0 en el momento marcado. Abajo, detalle del shield con los pines D3 y D2 señalados y el cable de tres hilos llegando.
> - **Elementos que deben señalarse:** mano, regla, sensor izquierdo, columna del monitor antes y después, pines D3 y D2 en el shield.
> - **Fuente técnica:** referencia del lenguaje Arduino, https://docs.arduino.cc/language-reference/, `digitalRead()` y constantes `HIGH`/`LOW`.
> - **Texto alternativo sugerido:** "Una mano a diez centímetros del sensor cambia la columna del monitor serie entre uno y cero, con los pines D3 y D2 señalados en el shield".

## Desafío: el cono invisible

Con el sketch escuchando D3, mueve tu mano lentamente en arco frente al sensor: al centro, a la izquierda, a la derecha, arriba. Marca en el aire (o pide que te ayuden a medir) hasta dónde de lado sigue detectando. Dibuja en el cuaderno el "cono de visión" de tu sensor visto desde arriba. Ahora sabes cuánto mundo ve de verdad.

## Si el monitor no cuenta la historia

| Síntoma | Qué revisar | Acción |
|---|---|---|
| No aparece nada en el monitor | ¿Puerto y baudios correctos? | Repite la lista de la Lección 08: placa Mega, su puerto, monitor a 9600 |
| La columna nunca cambia | ¿El LED de señal del sensor sí cambia con tu mano? | Si el LED cambia pero el número no, revisa que el cable OUT llegue a D3 (Lección 24) y que la constante diga 3; si el LED tampoco cambia, es físico: calibración (Lección 27) |
| Los valores saltan solos sin mover nada | ¿Estás en la zona inestable del umbral? | Recuerda la Lección 26: ajusta la calibración o cambia de distancia de trabajo |
| Cambia con movimientos lejos del frente | ¿Qué tan ancho era tu cono del desafío? | Es el campo de visión del módulo: anota el hallazgo, no es un error |
| Cambia al sonido o al tocar la mesa | ¿Algún cable flojo? | Pide al adulto revisar el conector de tres hilos con el USB retirado |

## Lecturas y videos para explorar

- [El espectro electromagnético y el infrarrojo](https://science.nasa.gov/ems/07_infraredwaves/) — Inglés; lectura NASA; 8 min. Aprenderás el espectro electromagnético y el infrarrojo. Esencial.
- [Sensores de PX-32](../../docs/reference/sensores.md) — Español; referencia interna; 6 min. Aprenderás sensores de px-32. Opcional.

La regla de integración de la referencia interna empieza contigo: un sensor gana permiso para mover motores solo después de mostrar datos comprensibles en Serial. Acabas de cumplir el primer requisito.

## Referencias técnicas de la clase

- [Referencia del lenguaje Arduino](https://docs.arduino.cc/language-reference/), `digitalRead()`, `pinMode()` con `INPUT`, y constantes `HIGH`/`LOW`.
- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), páginas 39 a 43, sensor izquierdo en D3 y derecho en D2.
- [Mapa canónico de conexiones](../../docs/reference/mapa-conexiones-robot.md), sensores IR de obstáculos.

## Cuéntale a papá

Muéstrale la columna de números cambiando con tu mano y explícale la diferencia entre un pin OUTPUT que empuja y un pin INPUT que escucha, con el ejemplo del LED del Blink. Cuéntale cuál número significa "detecté" en tu módulo y por qué lo escribiste en el cuaderno en vez de darlo por sabido. Pídele que invente una situación donde leer al revés (confundir 0 con 1) causaría un problema gracioso… o no tan gracioso.

Un sensor entrega un sí o un no. Pero PX-32 tiene dos sensores, y dos preguntas sí/no se combinan en cuatro respuestas posibles. En la [Lección 29](29-dos-sensores-cuatro-situaciones.md) aprendes a leerlas todas.
