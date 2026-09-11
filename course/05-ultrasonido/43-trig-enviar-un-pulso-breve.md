# Lección 43 — TRIG: enviar un pulso breve

## Cómo se le habla a un sensor que no tiene botones

El módulo ultrasónico de PX-32 no tiene botones, pantalla ni teclado. Es una placa con dos cilindros y cuatro pines. ¿Cómo se le ordena "grita ahora"?

La respuesta ya la conoces de la Lección 17, aunque no lo sepas: **hablándole con voltaje**. A Blink le ordenabas encender con `digitalWrite(13, HIGH)`. A este sensor se le ordena gritar subiendo un pin a 5 V durante un tiempo muy preciso: **10 microsegundos** de HIGH. No un segundo, no un milisegundo: diez microsegundos, la cuarta parte de un ciclo del grito de 40 kHz que calculaste en la Lección 40. Ese voltaje brevísimo es la orden completa; el módulo la recibe, y por su cuenta emite su ráfaga de ultrasonido y se queda esperando que le registres el regreso.

Hay un problema práctico, y es honesto reconocerlo: **tú no puedes ver un pulso de 10 µs**. Ni el ojo ni el oído lo captan. ¿Cómo sabes entonces que la orden salió? Hoy el truco será hacer que el programa **narre en el monitor serie cada paso que da**, como un relator de fútbol que cuenta la jugada milisegundo a milisegundo. El monitor no puede mostrarte el pulso; pero puede mostrarte la secuencia de órdenes, y con eso más lo que ya sabes del sensor, la evidencia es suficiente.

Un aviso de vocabulario antes de empezar: a esa subida breve de voltaje se le llama **pulso**. Lo usarás sin parar de aquí en adelante.

## Lo que necesitas

- PX-32 ensamblado, sobre la mesa, **con los motores sin energía** (sin baterías: hoy el único alimento es el USB).
- El módulo ultrasónico conectado (lo verificamos en el paso 1).
- Computador con Arduino IDE 2 y el cable USB.
- El sketch [43-trig-enviar-un-pulso-breve.ino](../../code/educational/43-trig-enviar-un-pulso-breve/43-trig-enviar-un-pulso-breve.ino).
- Tu cuaderno.

🟢 Programar, cargar y observar es tuyo. 🟡 Tu padre verifica el estado del robot antes de conectar el USB y presencia toda la sesión. 🔴 Si hay que tocar un cable del sensor o de potencia, lo hace él: siempre con USB fuera y todo apagado.

## Antes de cargar: verifica las cuatro líneas de vida del sensor

1. 🟡 Con PX-32 apagado y sin USB, mira con tu padre los **cuatro cables** que llegan al módulo ultrasónico desde el UART WiFi Shield (la placa sobre la Mega). El mapa canónico del robot dice exactamente qué debe haber:

   | Pin del módulo | Llega a | Para qué |
   |---|---|---|
   | VCC | 5V | alimentación |
   | Trig | **D30** | la orden de gritar (hoy) |
   | Echo | **D31** | el regreso del eco (mañana) |
   | GND | GND | referencia |

   En el manual del fabricante estos cables se muestran rojo (VCC), morado (Trig), verde (Echo) y negro (GND), pero **no confíes solo en el color**: los colores pueden cambiar entre unidades. Confía en el destino de cada cable, pin por pin, contra el [mapa de conexiones](../../docs/reference/mapa-conexiones-robot.md).

> **[PENDIENTE VISUAL]**
> - **Tipo:** fotografía anotada de las conexiones del módulo en el robot real.
> - **Objetivo:** que el niño verifique los cuatro cables contra el mapa sin adivinar.
> - **Descripción:** vista del frente del robot con el módulo ultrasónico y sus cuatro cables siguiéndose hasta el UART WiFi Shield; cada cable resaltado y rotulado con su pin de origen (VCC, Trig, Echo, GND) y su destino (5V, D30, D31, GND).
> - **Elementos que deben señalarse:** los cuatro cables uno a uno, los rótulos del shield, el módulo ultrasónico al otro extremo.
> - **Fuente técnica:** manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, página 29 (imagen local: [página 29](../../assets/osoyoo-manual/pagina-29-conexion-ultrasonico.png)) y [mapa canónico de conexiones](../../docs/reference/mapa-conexiones-robot.md).
> - **Texto alternativo sugerido:** "Cuatro cables del módulo ultrasónico seguidos hasta el shield, rotulados VCC-5V, Trig-D30, Echo-D31 y GND-GND".

2. 🔴 Si falta algún cable o no coinciden los pines, no lo conectes tú: el adulto lo corrige con todo apagado. Volver a intentar con un cable mal puesto puede dañar el módulo.

## El programa, línea por línea

3. 🟢 Con el USB conectado (por el adulto 🟡), abre el `.ino` en Arduino IDE y comprueba que el sketch del archivo es **idéntico** a este bloque:

```cpp
// Curso PX-32 - Leccion 43: enviar el pulso TRIG.
// Hoy solo aprendemos a dar la orden: todavia no medimos el eco.

const byte TRIG = 30;  // orden: cable desde D30 al pin Trig del modulo
const byte ECHO = 31;  // respuesta: cable desde el pin Echo a D31 (manana)

void setup() {
  pinMode(TRIG, OUTPUT);    // TRIG lo maneja la Mega
  digitalWrite(TRIG, LOW);  // empezar en reposo
  pinMode(ECHO, INPUT);     // ECHO lo maneja el modulo
  Serial.begin(9600);
  Serial.println("Leccion 43: solo TRIG.");
  Serial.println("El eco se mide en la Leccion 44.");
}

void loop() {
  Serial.println("--- nuevo pulso ---");

  Serial.println("1) TRIG en LOW  durante 2 us (reposo)");
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  Serial.println("2) TRIG en HIGH durante 10 us (la orden)");
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  Serial.println("3) TRIG vuelve a LOW (fin de la orden)");
  digitalWrite(TRIG, LOW);

  Serial.println("El modulo acaba de emitir su rafaga silenciosa.");
  delay(1000);  // pausa humana: un pulso por segundo
}
```

4. 🟢 **Lo conocido, primero.** `setup()`, `loop()`, `pinMode`, `digitalWrite`, `Serial` y `const`: todo viene de las lecciones 05 a 11. Hoy solo hay **dos palabras nuevas**, y una es familiar:

   - `delayMicroseconds(10)` es la hermana microscópica del `delay()` de Blink. `delay(1000)` espera 1000 **mili**segundos; `delayMicroseconds(10)` espera 10 **micro**segundos, cien mil veces menos. Es la primera vez que manejas tiempos más pequeños que el milisegundo: los conociste como unidad en la Lección 40 y ahora como herramienta.
   - `const byte ECHO = 31` prepara el pin D31 como `INPUT`, pero **nadie lo lee todavía**. Está declarado hoy para que el montaje quede completo desde el primer sketch; el eco llega en la Lección 44.

5. 🟢 **La secuencia LOW–HIGH–LOW, leída como música.** Fíjate en el orden exacto y en por qué es así: `LOW` 2 µs (asegurarnos de que el pin arranca limpio y bajo), `HIGH` 10 µs (la orden), `LOW` (bajar para que la próxima orden sea una subida nueva). Es como llamar a una puerta: tocar, esperar, retirar la mano. Los módulos tipo HC-SR04 piden exactamente este ritual; su hoja de datos lo describe: un pulso de al menos 10 µs en Trig dispara la ráfaga de 8 ciclos a 40 kHz.

6. 🟢 **Predice antes de cargar.** Escribe en el cuaderno qué cinco líneas crees que aparecerán en el monitor cada segundo, y en qué orden. Piensa también: ¿se moverá algo en el robot? ¿Oirás algo? (Respuestas: nada se moverá —no hay órdenes a motores—, y nada oirás —40 kHz están fuera de tu oído, Lección 41—. Si "oyes" un clic, es el servo o algo suelto: detente y revisa con tu padre.)

7. 🟡 Tu padre comprueba la selección de placa (Mega 2560) y puerto, sube el sketch y abre el monitor serie a **9600 baudios** (Lección 08). Si el IDE marca error de compilación, revisa la tabla de abajo antes de tocar nada más.

8. 🟢 **Observa al relator trabajar.** Deben aparecer, una vez por segundo, las cinco líneas de tu predicción: la secuencia completa y el anuncio de la ráfaga. Verifica línea por línea contra tu cuaderno. Ese "rafaga silenciosa" no es adorno: en ese instante el cilindro T del sensor **realmente emitió** un chillido de 40 kHz que rebotó en la pared de tu cuarto y regresó al cilindro R. Está pasando de verdad, a un palmo de tu cara, y ni tú ni nadie en la habitación lo percibe. Solo la Mega podría contarlo… y aprenderá mañana.

9. 🟢 **Cambia una sola cosa.** Modifica únicamente el `delay(1000)` final a `delay(3000)` y vuelve a subir. El relator ahora habla cada tres segundos: la orden es la misma; solo cambia el ritmo humano. Déjalo en 1000 al terminar, para que el archivo quede como el original.

10. 🟢 **Cierre seguro.** Cierra el monitor, desconecta el USB (lo hace el adulto si prefieres) y anota en el cuaderno la evidencia del día: "la orden de gritar es un pulso de 10 µs en D30; secuencia LOW–HIGH–LOW; no hay nada que oír ni ver, la evidencia es la narración del monitor".

## Si no funciona

| Síntoma | Qué revisar | Acción |
|---|---|---|
| El monitor no muestra nada | ¿9600 baudios? ¿El puerto correcto? | Revisa con la prueba de desconexión de la Lección 05: el puerto desaparece al retirar el USB |
| Las líneas salen con símbolos raros | ¿Otra velocidad en el monitor? | Baja el selector del monitor a 9600 |
| Error de compilación | ¿Copiaste una línea incompleta o borraste un `;`? | Compara con el bloque de arriba carácter por carácter; el IDE subraya la línea sospechosa |
| Todo sale pero no pasa nada más | ¿Esperabas oír o ver el grito? | Es correcto así: 40 kHz son inaudibles y no hay motores conectados a este sketch |
| El monitor repite más rápido de lo esperado | ¿Cambiaste `delay(1000)` y lo dejaste así? | Devuélvelo a 1000: un pulso por segundo es el ritmo pensado para leer con calma |

## Desafío: el pulso más largo del mundo

¿Qué pasaría si en vez de 10 µs dejaras TRIG en HIGH durante un segundo entero? Piénsalo antes de probarlo, y escríbelo: la hoja de datos dice que el módulo necesita *al menos* 10 µs para **iniciar** la ráfaga; después de eso, mantener el pulso más tiempo no grita más fuerte ni más largo — la orden es un disparo, no un volumen. Si quieres comprobarlo en el monitor, cambia solo `delayMicroseconds(10)` por `delayMicroseconds(50)`: la narración no cambia en nada perceptible. Cinco veces más de orden… y el mismo grito de siempre. No todas las magnitudes de un programa funcionan como perillas.

## Lecturas y videos para explorar

- [Velocidad, frecuencia y longitud de onda del sonido](https://openstax.org/books/physics/pages/14-1-speed-of-sound-frequency-and-wavelength) — Inglés; libro abierto; 12 min. Aprenderás velocidad, frecuencia y longitud de onda del sonido. Esencial.
- [Biblioteca Servo](https://docs.arduino.cc/libraries/servo/) — Inglés; referencia oficial Arduino; 10 min. Aprenderás biblioteca servo. Opcional.

## Referencias técnicas de la clase

- [Hoja de datos del módulo HC-SR04 (SparkFun)](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf): disparo con pulso de 10 µs en Trig y ráfaga de 8 ciclos a 40 kHz.
- [`delayMicroseconds()` en la referencia de Arduino](https://docs.arduino.cc/language-reference/en/functions/time/delaymicroseconds/): pausas en microsegundos.
- [Mapa canónico de conexiones](../../docs/reference/mapa-conexiones-robot.md): Trig → D30, Echo → D31, según manual OSOYOO p. 29.

## Cuéntale a papá

Muéstrale el monitor en acción y explícale por qué no se oye ni se ve nada, aunque el sensor esté gritando frente a ustedes en ese mismo instante: 10 µs de orden, 40 kHz de grito, 25 µs por ciclo. Pregúntale si puede aplaudir durante 10 microsegundos (pista: no, y tú tampoco — la Lección 40 ya lo demostró). Marca la casilla 43 en [PROGRESS.md](../../PROGRESS.md).

La orden ya sale. Falta el cronómetro que mida el regreso: en la [Lección 44](44-echo-medir-una-duracion.md) la Mega aprende a esperar el eco.
