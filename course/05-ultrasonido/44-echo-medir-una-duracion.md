# Lección 44 — ECHO: medir una duración

## El cronómetro que llevaba la Mega escondido

Ayer PX-32 aprendió a gritar. El monitor narraba la orden, y en ese mismo instante un chillido de 40 kHz rebotaba en las paredes de tu cuarto y volvía a morir en el cilindro R, sin que nadie lo registrara. Hoy vamos a instalar al árbitro: un cronómetro capaz de medir microsegundos, que ya venía escondido en el lenguaje de Arduino.

Se llama `pulseIn()` y hace una sola cosa, pero la hace con una paciencia de relojero: **espera a que un pin suba (o baje) y mide cuánto tiempo se quedó arriba**. Nosotros le pedimos: "mira el pin D31; cuando el módulo reciba el eco, ese pin subirá a 5 V; cronometra cuánto dura esa subida". El módulo tiene la cortesía de mantener su pin Echo en alto **exactamente el tiempo que el sonido estuvo de viaje**. Así, sin reloj de pared ni cronómetro de pulsera, el viaje de ida y vuelta de la Lección 42 queda convertido en un número: **microsegundos**.

Pero hay un problema serio que un robot no puede ignorar: ¿y si el eco **nunca llega**? (El sensor apunta a un pasillo vacío, o el objeto absorbió el sonido.) `pulseIn()` esperaría… y esperar… y esperar. Por defecto, la función espera **un segundo entero** sin hacer nada más — para un programa de robot, un segundo congelado es una eternidad: recuerda que en la Lección 38 el bucle completo de seguimiento corría **veinte veces por segundo**. La solución se llama **timeout**: le avisamos a `pulseIn()` cuánto puede esperar como máximo antes de rendirse y devolver un **0**, que en nuestro código significará "no hubo eco fiable". Vamos a usar 30 000 µs, que le da al sonido tiempo de recorrer unos cinco metros de ida y vuelta — más que suficiente en un cuarto normal.

## Lo que necesitas

- PX-32 ensamblado, con el módulo ultrasónico verificado en la Lección 43 (Trig → D30, Echo → D31), **sin baterías**.
- Computador con Arduino IDE 2 y cable USB.
- El sketch [44-echo-medir-una-duracion.ino](../../code/educational/44-echo-medir-una-duracion/44-echo-medir-una-duracion.ino).
- Un objeto de prueba: un libro grande parado como muralla, o una caja de cereal llena.
- Cinta métrica o regla para medir distancias reales.
- Tu cuaderno para la tabla de mediciones.

🟢 La programación y las mediciones son tuyas. 🟡 Tu padre presencia la sesión USB. 🔴 Cables y energía, siempre el adulto.

## El programa, con el cronómetro a bordo

1. 🟢 Abre el `.ino` y verifica que sea idéntico a este bloque:

```cpp
// Curso PX-32 - Leccion 44: medir cuanto dura el eco (ECHO).
// El monitor muestra microsegundos crudos: todavia sin convertir.

const byte TRIG = 30;
const byte ECHO = 31;

// Esperamos a que el eco empiece como maximo 30000 us
// (alrededor de 5 m de viaje de ida y vuelta).
const unsigned long TIMEOUT_US = 30000UL;

unsigned long medirEcoEnUs() {
  digitalWrite(TRIG, LOW);   // secuencia de la Leccion 43
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  return pulseIn(ECHO, HIGH, TIMEOUT_US);  // el cronometro
}

void setup() {
  pinMode(TRIG, OUTPUT);
  digitalWrite(TRIG, LOW);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
  Serial.println("Leccion 44: duracion del eco en microsegundos.");
}

void loop() {
  unsigned long us = medirEcoEnUs();

  if (us == 0) {
    // pulseIn espero en vano a que ECHO subiera.
    Serial.println("SIN ECO: el pulso nunca empezo");
  } else if (us > 23200UL) {
    // 23200 us equivale a unos 400 cm: fuera de alcance util.
    Serial.print("ECO DEMORADO: ");
    Serial.print(us);
    Serial.println(" us (fuera de alcance)");
  } else {
    Serial.print("eco: ");
    Serial.print(us);
    Serial.println(" us");
  }

  delay(200);
}
```

2. 🟢 **Lo nuevo, en tres pedazos:**

   - `unsigned long` es el tipo de número para contar microsegundos sin desbordarse — el mismo tipo que conoció el contador de la Lección 08, elegido por la misma razón: números que crecen y crecen sin quedarse sin espacio. Aquí garantiza que 30 000 y mucho más caben sobrados.
   - `medirEcoEnUs()` es una **función con retorno**, como las de la Lección 11: encapsula la secuencia de gritar (ayer) y cronometrar (hoy) en una sola orden reutilizable. A partir de ahora, cada lección nueva del sensor la copiará tal cual: escribir una vez, usar siempre.
   - `pulseIn(ECHO, HIGH, TIMEOUT_US)` es el corazón del día: "espera en D31 una señal HIGH, máxime `TIMEOUT_US` microsegundos; devuelve cuánto duró, o 0 si nunca empezó".

3. 🟢 **Los dos modos de fracaso, contados con honestidad.** El `if` del `loop()` distingue tres mundos: eco normal (número en µs), `SIN ECO` (el pin nunca subió — 0), y `ECO DEMORADO` (el pin subió, pero el viaje fue tan largo que el resultado pasa de 23 200 µs ≈ 400 cm, el alcance útil declarado por la hoja de datos). Fíjate en algo que sorprende a muchos: **"no hubo eco" puede verse como 0 o como un número gigante**, según cómo se comporte el módulo cuando el sonido se pierde. Tu robot trata ambos casos como "nada fiable adelante", que es lo único seguro que se puede concluir. La distinción exacta la verás en la actividad.

4. 🟢 **Predice antes de cargar.** En el cuaderno, completa: "si pongo la mano a unos 17 cm del sensor, el sonido recorre ___ cm en total, así que el monitor debería mostrar unos ___ µs". (Pista con la Lección 42: 34 cm de viaje total; 34 / 0,0343 ≈ **991 µs**. Casi exactamente 1000: la mano a 17 cm es tu "baliza" de mil microsegundos.)

5. 🟡 Tu padre conecta el USB, verifica placa y puerto, sube el sketch y abre el monitor a 9600 baudios. Aparecerá una línea nueva cada 200 ms — cinco por segundo, un ritmo pensado para leer sin marearte.

## El experimento: el números crecen con la distancia

6. 🟢 **La baliza de los 1000 µs.** Coloca tu mano (o el libro parado) a unos 17 cm frente a los cilindros del sensor, medidos con la regla. Lee el monitor: deben aparecer valores cercanos a 1000 µs, saltando un poco de línea en línea. Copia cinco valores seguidos en el cuaderno; son tu primer grupo de datos real.

7. 🟢 **Doble distancia, doble número.** Aleja el objeto a unos 34 cm y copia otros cinco valores. Compara los grupos: ¿se duplicaron? La regla que estás descubriendo se escribe `~58 µs por cada centímetro de distancia`: 17 cm → ~991 µs; 34 cm → ~1982 µs. Grábala: **1 cm ≈ 58 µs de eco**. No la vas a necesitar mañana, porque la derivaremos desde la física; pero es la baliza para revisar si una medición es razonable.

8. 🟢 **A ciegas, sin objeto.** Retira el objeto por completo y apunta el sensor hacia el pasillo o el lado más lejano y abierto del cuarto. Observa el monitor durante unos diez segundos y anota **qué caso de fracaso produce tu módulo**: ¿`SIN ECO` (0), o `ECO DEMORADO` con un número enorme? Los módulos tipo HC-SR04 suelen mantener Echo en alto un largo rato (del orden de decenas de milisegundos) antes de rendirse; otros cortan antes. No hay respuesta única: **la de tu robot es la que vale**, y anotarla en el cuaderno es exactamente el tipo de evidencia que este curso colecciona (como hiciste con el lado de IR1 en la Lección 34).

9. 🟢 **La prueba del algodón.** Ahora pon frente al sensor, a unos 15 cm, una almohada o una toalla doblada. Anota qué pasa: muchos menos ecos, o números erráticos, o SIN ECO. ¿Por qué? La Lección 25 te dio la pista con la luz y el color negro: hay materiales que **absorben** en vez de rebotar. Una almohada se traga el sonido; un libro duro lo devuelve. Un robot que ignore esto "pensaría" que no hay nada delante… y avanzaría directo hacia la almohada. Por eso la Lección 49 tratará la falta de eco como peligro, no como "camino libre".

10. 🟢 **Cierre.** Cierra el monitor, USB fuera (el adulto), y deja constancia en el cuaderno: la tabla de tus mediciones, el caso de fracaso de tu módulo y el comportamiento con la almohada.

## Si no funciona

| Síntoma | Qué revisar | Acción |
|---|---|---|
| Siempre `SIN ECO` con objeto a 17 cm | ¿El cable de Echo llegó a D31 y no a otro pin? | Compara contra el mapa con tu padre 🟡; el manual del fabricante advierte que una conexión errada del sensor arruina su demo (pp. 26–33) |
| Siempre `ECO DEMORADO` aunque el objeto esté cerca | ¿El objeto es blando o está inclinado? | Usa un libro duro y plano, de frente al sensor (la Lección 46 estudia esto a fondo) |
| Los números saltan mucho | ¿Mueves la mano sin querer? ¿El robot se desliza? | Apoya el objeto (libro parado) y no toques el robot entre lecturas |
| Nada aparece en el monitor | ¿9600 baudios, puerto y placa correctos? | Repite la verificación de la Lección 43; el sketch de ayer funcionó, este solo añade `pulseIn` |
| Aparecen 0 mezclados con números normales | ¿La distancia está justo en el límite? | Prueba a 20–30 cm, donde el eco es robusto; los saltos al borde son normales |

## Desafío: el lápiz invisible

Prueba objetos cada vez más delgados frente al sensor a 15 cm: el libro, una regla de canto, un lápiz, un cordón. Anota desde cuál el eco se vuelve inestable o desaparece. El cono de ultrasonido del sensor es ancho y el eco necesita superficie suficiente para regresar: acabas de descubrir el **tamaño mínimo de objeto** que PX-32 puede ver. Ese límite explicará en la Lección 49 por qué un poste delgado es un mal obstáculo de prueba.

## Lecturas y videos para explorar

- [Velocidad, frecuencia y longitud de onda del sonido](https://openstax.org/books/physics/pages/14-1-speed-of-sound-frequency-and-wavelength) — Inglés; libro abierto; 12 min. Aprenderás velocidad, frecuencia y longitud de onda del sonido. Esencial.
- [Biblioteca Servo](https://docs.arduino.cc/libraries/servo/) — Inglés; referencia oficial Arduino; 10 min. Aprenderás biblioteca servo. Opcional.

## Referencias técnicas de la clase

- [`pulseIn()` en la referencia de Arduino](https://docs.arduino.cc/language-reference/en/functions/advanced-io/pulseIn/): devuelve la duración del pulso en microsegundos; 0 si vence el tiempo de espera (por defecto, un segundo).
- [Hoja de datos del módulo HC-SR04 (SparkFun)](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf): ancho del pulso Echo proporcional a la distancia; alcance útil 2–400 cm.
- [Mapa canónico de conexiones](../../docs/reference/mapa-conexiones-robot.md): Echo → D31.

## Cuéntale a papá

Muéstrale el monitor con tu mano a 17 cm y explícale la baliza: "mil microsegundos de eco son diecisiete centímetros de distancia". Enséñale el caso de fracaso de tu módulo sin objeto y cuéntale por qué un robot serio necesita distinguir "nada adelante" de "no puedo medir". Marca la casilla 44 en [PROGRESS.md](../../PROGRESS.md).

Ya sabes gritar y cronometrar. En la [Lección 45](45-de-microsegundos-a-centimetros.md) convertimos esos microsegundos en centímetros de verdad, con la fórmula completa.
