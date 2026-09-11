# Lección 48 — Escaneo espacial

## El faro que barre la noche con un cuaderno en la mano

Los faros de los puertos no se encienden y ya: **giran**, y su haz barre el mar en círculos. El capitán de un barco, en la oscuridad, no ve el haz directamente — ve el **destello** cuando pasa por su rumbo, y con su cronómetro y la carta de la costa deduce dónde está. Un faro giratorio es un solo foco convertido en un mapa completo de la noche.

Hoy PX-32 se convierte en faro, y tú en el capitán que dibuja la carta. Todo lo del bloque se une en una sola rutina de cuatro tiempos: **mover** la cabeza a un ángulo, **esperar** a que la mecánica se asiente, **medir** la distancia con el ultrasonido, **anotar** el par ángulo-distancia. Mover, esperar, medir, anotar. Tres veces: izquierda, centro, derecha. Al final, el monitor entrega una tabla — y esa tabla, dibujada en tu cuaderno, es un pequeño **mapa polar**: un mapa donde cada punto queda definido no por "cuánto al este y cuánto al norte", sino por **ángulo y distancia** desde quien mira. Es exactamente cómo un radar organiza el mundo, y hoy tu cuaderno va a oler a radar.

La palabra del día es **barrido** ("sweep" en inglés, y verás ese nombre en mil proyectos de robotics): recorrer una serie de direcciones tomando una muestra en cada una.

## Lo que necesitas

- PX-32 ensamblado, servo alineado en 90° frente al chasis (Lección 47) y sensor verificado (Lecciones 43–46).
- Tu cuaderno abierto en la página del dato del ángulo 45° ("45 apunta hacia mi ___").
- Computador, Arduino IDE 2, USB… y baterías 18650 a cargo del adulto para la fase completa (el servo necesita su energía, como aprendiste ayer).
- El sketch [48-escaneo-espacial.ino](../../code/educational/48-escaneo-espacial/48-escaneo-espacial.ino).
- Dos obstáculos de prueba: dos libros parados o cajas, que puedas poner a los costados del robot.
- Un despeje de medio metro al frente del robot: la mesa desocupada o el piso con área libre.

🟢 Programar, observar y dibujar el mapa es tuyo. 🟡 El adulto presencia USB y fase de batería. 🔴 Baterías e interruptor, siempre el adulto.

## El programa: mover, esperar, medir, anotar

1. 🟢 Abre el `.ino` y verifica que coincida con este bloque:

```cpp
// Curso PX-32 - Leccion 48: escaneo espacial.
// Mover, esperar el asentamiento, medir, informar: tres direcciones.

#include <Servo.h>

const byte TRIG = 30;
const byte ECHO = 31;
const byte PIN_SERVO = 13;
const unsigned long TIMEOUT_US = 30000UL;
const float SONIDO_CM_POR_US = 0.0343;

Servo cabeza;

// Los tres angulos del barrido (array como en la Leccion 35).
const int ANGULOS[3] = { 45, 90, 135 };

float medirDistanciaCm() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  unsigned long us = pulseIn(ECHO, HIGH, TIMEOUT_US);

  if (us == 0 || us > 23200UL) {
    return -1.0;  // -1 = lectura no fiable (convenio de esta leccion)
  }

  return us * SONIDO_CM_POR_US / 2.0;
}

void setup() {
  pinMode(TRIG, OUTPUT);
  digitalWrite(TRIG, LOW);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
  cabeza.attach(PIN_SERVO);
  cabeza.write(90);  // empezar mirando al frente
  delay(1000);
  Serial.println("Leccion 48: escaneo 45 / 90 / 135.");
}

void loop() {
  for (byte i = 0; i < 3; i++) {
    cabeza.write(ANGULOS[i]);
    delay(500);  // asentamiento: la mecanica necesita su tiempo

    float cm = medirDistanciaCm();

    Serial.print("angulo ");
    Serial.print(ANGULOS[i]);
    Serial.print(": ");

    if (cm < 0) {
      Serial.println("sin eco fiable");
    } else {
      Serial.print(cm, 1);
      Serial.println(" cm");
    }
  }

  Serial.println("--- barrido completo: vuelta al frente ---");
  cabeza.write(90);
  delay(1500);
}
```

2. 🟢 **Todo lo que hay adentro ya es tuyo.** Repasa la lista de proveniencia — es el resumen más bonito del bloque: `ANGULOS[3]` es un array (Lección 35) que guarda los tres ángulos; el `for` con `byte i` los recorre uno a uno (Lección 10); `medirDistanciaCm()` es la fusión de las Lecciones 44 y 45 — gritar, cronometrar, convertir, y declarar `-1` cuando el eco no es fiable; `cabeza.write()` es el cuello de ayer; el `delay(500)` tras cada movimiento es la paciencia mecánica. Lo único verdaderamente nuevo es un **convenio**: usar `-1.0` como respuesta para "esto no es una distancia válida". Como ninguna distancia real puede ser negativa, `-1` queda libre para significar "no fiable" sin confundirse con una medición.

3. 🟢 **Por qué 500 ms de espera.** El servo es rápido pero no instantáneo, y mientras vibra tras llegar, sus cilindros se mueven con él: medir en plena vibración es fotografiar a alguien corriendo. El `delay(500)` es el "quédate quieto un momento" del fotógrafo. Pruébalo mentalmente: ¿qué pasaría con 50 ms? (El servo apenas va llegando: lecturas con el sensor a medio camino — un barrido de mentira.)

4. 🟢 **Predice el barrido con obstáculos.** Antes de cargar, monta la escena: un libro parado a unos 25 cm del costado donde apunta 45°, otro a unos 25 cm del lado de 135°, y el frente (90°) despejado hacia el espacio más abierto que tengas (una pared lejana o el borde libre de la mesa). Escribe tu predicción: "ángulo 45: ___ cm, ángulo 90: ___ o sin eco fiable, ángulo 135: ___ cm". Usa tu cuaderno de la Lección 47 para saber cuál libro queda en cuál ángulo.

5. 🟡 **Fase USB.** El adulto conecta, sube el sketch, monitor a 9600. Igual que ayer, es posible que el servo no se mueva sin baterías; en tu robot puede que sí. La fase de verdad es la siguiente.

6. 🔴 **Fase batería.** El adulto instala las celdas y enciende, robot apoyado y manos lejos del soporte. Al arrancar, cabeza al frente 1 s, y luego el ciclo: 45… pausa… "angulo 45: 24,9 cm"… 90… 135… y vuelta al frente. Cada barrido completo tarda ~3 s, y el monitor va dictando la tabla.

## El experimento: el capitán dibuja su carta

7. 🟢 **Primera carta.** Copia en el cuaderno la tabla completa de un barrido con los dos libros montados. Deben verse las tres direcciones, cada una con su número (o su "sin eco fiable"). Compara contra tu predicción del paso 4 y explica cualquier diferencia (¿el libro estaba a la distancia que creías? ¿más inclinado?).

8. 🟢 **Dibuja el mapa polar.** En el cuaderno: un punto central (PX-32), tres flechas — la del centro al frente, una a cada costado según TU dato de la Lección 47 (45 hacia tu izquierda o derecha, tal como lo anotaste) — y sobre cada flecha, una rayita cruzada con la distancia medida escrita al lado. Ponle objetos dibujados donde están los libros. **Ese dibujo es un mapa del mundo construido por tu robot.** Nadie te lo dio: PX-32 lo midió.

> **[PENDIENTE VISUAL]**
> - **Tipo:** ilustración de mapa polar paso a paso.
> - **Objetivo:** enseñar a traducir la tabla ángulo-distancia del monitor a un dibujo tipo radar.
> - **Descripción:** panel izquierdo con la tabla "angulo 45: 24,9 cm / angulo 90: sin eco / angulo 135: 25,2 cm"; panel derecho con el robot como punto central, tres flechas a 45, 90 y 135 grados, ticks de distancia sobre cada flecha y los dos libros dibujados en sus posiciones.
> - **Elementos que deben señalarse:** punto central rotulado PX-32, las tres flechas con su ángulo, ticks con centímetros, rótulo "sin eco fiable" en la flecha central, libros-objetivo.
> - **Fuente técnica:** elaboración propia del curso sobre el barrido del manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, pp. 31–33 (demo de evasión del fabricante con lecturas a 45/90/135).
> - **Texto alternativo sugerido:** "Tabla de barrido al lado de un mapa polar con tres flechas y las distancias medidas marcadas sobre cada una".

9. 🟢 **Cambia una sola cosa: mueve un libro.** Corre el libro del lado 45 unos 10 cm más lejos y deja el otro quieto. Pulsa RESET y copia el nuevo barrido: solo la dirección 45 debió cambiar. Esa es la firma de un buen instrumento: responde a lo que cambió y no a lo que no.

10. 🟢 **El caso del pasillo vacío.** Quita los dos libros y apunta el frente hacia el espacio más abierto disponible. El barrido mostrará los tres como "sin eco fiable" o números grandes y desparejos, según tu módulo (Lección 44, tu anotación). En el mapa polar esto se dibuja… con nada: un mundo sin obstáculos a la vista. Anótalo así — "la ausencia de eco también es información: no hay nada a mi alcance".

11. 🟢 **Cierre.** El adulto apaga y retira las celdas 🔴. Tu cuaderno debe quedar con: la tabla del primer barrido, el mapa polar, y la constancia de que al mover un solo objeto solo cambió una sola dirección.

## Si no funciona

| Síntoma | Qué revisar | Acción |
|---|---|---|
| Las distancias no corresponden al lado correcto | ¿Tu dato de la Lección 47 está bien anotado? | Verifica de nuevo desde atrás del robot: 45 y 135 se intercambian si te paras enfrente en vez de detrás |
| El ángulo 90 marca 4 cm siempre | ¿Hay algo frente al robot que olvidaste? | La mesa, un borde, tu propia mano apoyada: mira qué hay a 4 cm al frente de los cilindros |
| Las lecturas salen a medias de camino | ¿La espera de asentamiento es corta? | No bajes `delay(500)` a menos que veas al servo firmemente detenido antes de 500 ms |
| El servo no gira pero el monitor avanza | ¿Fase USB sin baterías? | Recuerda la Lección 47: el músculo del servo vive del lado de las baterías; pasa a fase batería 🔴 |
| "sin eco fiable" en todas partes | ¿Obstáculos blandos, inclinados o lejos? | Repite con libros duros a 25 cm: la configuración robusta de la Lección 46 |
| Los números cambian entre barridos sin tocar nada | ¿El robot se mueve, la mesa vibra, hay alguien hablando cerca? | Sujeta el robot, apoya los codos: el sonar de 25 cm no perdona temblores |

## Desafío: el barrido de cinco puntos

¿Puedes ampliar el mapa sin ampliar los riesgos? Modifica solo el array: `const int ANGULOS[5] = { 45, 70, 90, 110, 135 };` y el `for` para recorrer 5 (`i < 5`). Carga (fase batería con el adulto 🔴) y copia el barrido de cinco puntos: ¿apareció algún obstáculo entre 45 y 90 que el barrido de tres no veía? Esa es la diferencia entre **resolución** de mapas: más muestras, más detalle, más tiempo por barrido. Nada es gratis. Al terminar, devuelve el archivo a la versión de tres puntos.

## Lecturas y videos para explorar

- [Velocidad, frecuencia y longitud de onda del sonido](https://openstax.org/books/physics/pages/14-1-speed-of-sound-frequency-and-wavelength) — Inglés; libro abierto; 12 min. Aprenderás velocidad, frecuencia y longitud de onda del sonido. Esencial.
- [Biblioteca Servo](https://docs.arduino.cc/libraries/servo/) — Inglés; referencia oficial Arduino; 10 min. Aprenderás biblioteca servo. Opcional.

## Referencias técnicas de la clase

- [Biblioteca Servo de Arduino](https://docs.arduino.cc/libraries/servo/): `write()` y `attach()` en producción.
- [`pulseIn()` en la referencia de Arduino](https://docs.arduino.cc/language-reference/en/functions/advanced-io/pulseIn/): temporización y timeout dentro de `medirDistanciaCm()`.
- [Manual OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), pp. 31–33: demo del fabricante que gira el sensor para comparar los lados antes de decidir.

## Cuéntale a papá

Muéstrale el mapa polar de tu cuaderno y cuéntale que su hijo lo dibujó con datos que midió el robot solo: tres direcciones, tres distancias, dos libros localizados sin tocarlos. Explícale el convenio del `-1` ("cuando el eco no es fiable, el número dice que no es un número") y por qué el robot siempre regresa la cabeza al frente antes de repetir. Marca la casilla 48 en [PROGRESS.md](../../PROGRESS.md).

El mapa existe. Falta la decisión: en la [Lección 49](49-evitar-obstaculos.md), el hito del bloque — PX-32 usará este barrido para **esquivar obstáculos conduciendo solo**.
