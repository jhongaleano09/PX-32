# Lección 40 — Frecuencia y período

## Tu cuerpo ya mide frecuencias sin saberlo

Ponte la mano en el pecho y siente tu corazón. Un latido… otro… otro. Si eres como la mayoría de la gente, late más o menos **una vez por segundo** cuando estás tranquilo. En la clase de gimnasia, después de correr, sube a dos o tres por segundo. Acabas de hacer, sin saberlo, una medición de **frecuencia**: cuántas veces por segundo se repite algo.

Los sonidos también son repeticiones, y muy rápidas. Ayer viste que el sonido es un empujón que viaja por el aire. Pero un empujón solo no es una voz ni un silbido: una voz es una **sucesión de empujones**, uno tras otro, como aplausos encadenados. La frecuencia de esa sucesión es lo que tus oídos traducen como "grave" (pocos empujones por segundo) o "agudo" (muchísimos).

Hoy vas a medir frecuencias con tu cuerpo, con un reloj y con la calculadora, y vas a llegar hasta una frecuencia que ningún humano ha aplaudido jamás: la del grito secreto del sensor de PX-32.

## Dos palabras que son la misma idea al revés

- **Frecuencia (f):** cuántas repeticiones ocurren **en un segundo**. Se mide en **hertz (Hz)**, en honor a Heinrich Hertz, el físico que demostró la existencia de las ondas de radio (lo volverás a encontrar en el bloque de Bluetooth). 4 Hz significa "cuatro veces por segundo".
- **Período (T):** cuánto **dura una sola repetición**. Se mide en segundos (o en fracciones). Es la misma información mirada al revés: si aplaudes 4 veces por segundo, cada aplauso dura un cuarto de segundo.

Y ahí está la fórmula más importante de hoy, tan simple que casi parece trampa:

```text
período = 1 / frecuencia
frecuencia = 1 / período
```

Si algo se repite 2 veces por segundo, cada repetición dura medio segundo. Si se repite 10 veces por segundo, dura un décimo. Cuanto más frecuencia, menos período. Son inversos, como "cuántos pasos das" y "qué tan largos son tus pasos" para recorrer la misma distancia.

## Lo que necesitas

- Un reloj con segundero, cronómetro o el que tenga tu padre en el teléfono (que él lo sostenga).
- Calculadora (la del computador sirve).
- Tu cuaderno para la tabla.
- Tus manos. Hoy PX-32 descansa: no se usa el robot.

🟢 Todo lo haces tú; solo necesitas a tu padre como árbitro de tiempo.

## El experimento: hasta dónde llega tu cuerpo

1. 🟢 **Aplausos de 1 Hz.** Con tu padre cronometrando 10 segundos, aplaude **una vez por segundo** (él te marca el ritmo con el dedo al principio, luego te suelta). Deben contar unos 10 aplausos en 10 segundos. Anota en el cuaderno: `1 Hz -> período 1 segundo`.

2. 🟢 **Sube a 2 Hz.** Ahora dos aplausos por segundo durante 10 segundos (unos 20 en total). Calcula con la fórmula: `período = 1/2 = 0,5 segundos`. Compruébalo con el cronómetro si quieres: entre un aplauso y el siguiente pasan dos mitades de segundo.

3. 🟢 **Ahora 4 Hz y luego 8 Hz.** Duplica el ritmo. Llega un punto —entre 6 y 10 aplausos por segundo— donde el aplauso deja de ser aplauso y se vuelve un tractor. Ese es el **límite de tus manos**. Los músculos no dan para más. Anota tu récord personal: "mis manos llegan a ___ Hz".

4. 🟢 **La tabla de la calculadora.** Copia esta tabla y complétala con `período = 1 / frecuencia`:

   | Frecuencia | Cálculo | Período |
   |---|---|---|
   | 1 Hz | 1/1 | 1 s |
   | 2 Hz | 1/2 | 0,5 s |
   | 10 Hz | 1/10 | ___ |
   | 20 000 Hz (lo más agudo que oyes) | 1/20000 | ___ |
   | 40 000 Hz (el grito de PX-32) | 1/40000 | ___ |

5. 🟢 **Los microsegundos entran en escena.** Completa las dos últimas filas y mira lo que obtienes: 1/20 000 s = 0,00005 s, y 1/40 000 s = 0,000025 s. Escribir tantos ceros cansa y confunde, así que los científicos usan una unidad más cómoda: el **microsegundo (µs)**, que es la millonésima parte de un segundo. Entonces: 0,000025 s = 25 µs. **El grito de PX-32 tiene un período de 25 µs.** Graba ese número: en la Lección 43 vas a escribir código que manda órdenes de 10 µs, ¡más cortas aún que un ciclo del grito!

6. 🟢 **Verifica que lo entendiste** respondiendo en el cuaderno: si un zumbido tiene una frecuencia de 100 Hz, ¿cuánto dura cada ciclo? (Respuesta para comprobar: 0,01 s, es decir 10 000 µs). ¿Y uno de 2 000 Hz? (0,5 ms = 500 µs).

Fíjate en algo honesto: "lo más agudo que oyes" (20 000 Hz) es un valor típico del oído humano joven; el límite exacto de cada persona varía y baja con la edad. Los 40 000 Hz del módulo no son un capricho: el fabricante de este tipo de sensores los eligió justo **por encima** de lo que cualquier persona oye, para que el robot grite sin molestar a nadie. Mañana veremos ese límite con lupa.

## Desafío: el metrónomo humano

Pide a tu padre que aplauda a un ritmo constante sin decirte la frecuencia. Tú cronometras 10 segundos, cuentas sus aplausos y calculas la frecuencia y el período. Luego intercambien papeles. El que calcule el período más exacto sin calculadora (de cabeza, con fracciones) gana un punto. Cinco rondas.

## Si no funciona

| Síntoma | Qué revisar | Acción |
|---|---|---|
| No logro mantener el ritmo | ¿Intentas mirar el cronómetro mientras aplaudes? | Que tu padre cuente los segundos en voz alta; tú solo aplaudes |
| Me pierdo con tantos ceros | ¿Estás escribiendo 0,000025 en lugar de pensar en µs? | Usa microsegundos desde la fila de 10 Hz: 1/10 s = 100 000 µs, y baja dividiendo |
| La calculadora me da notación rara (2,5e-5) | ¿Usas la calculadora del computador en modo científico? | Pídele a tu padre que te explique: 2,5e-5 significa 2,5 × 0,00001, o sea 25 µs |
| No sé si mi corazón late 1 Hz de verdad | ¿Cronometraste 15 segundos y contaste latidos? | Cuenta los latidos de 15 s y divide entre 15: esa es tu frecuencia cardíaca en Hz |

## Lecturas y videos para explorar

- [Velocidad, frecuencia y longitud de onda del sonido](https://openstax.org/books/physics/pages/14-1-speed-of-sound-frequency-and-wavelength) — Inglés; libro abierto; 12 min. Aprenderás velocidad, frecuencia y longitud de onda del sonido. Esencial.
- [Biblioteca Servo](https://docs.arduino.cc/libraries/servo/) — Inglés; referencia oficial Arduino; 10 min. Aprenderás biblioteca servo. Opcional.

La sección de frecuencia y período de OpenStax tiene exactamente la fórmula de hoy con ejemplos resueltos.

## Referencias técnicas de la clase

- [OpenStax Physics, sección 14.1](https://openstax.org/books/physics/pages/14-1-speed-of-sound-frequency-and-wavelength): definición de frecuencia, período y su relación inversa.
- [Referencia del lenguaje Arduino, `delayMicroseconds()`](https://docs.arduino.cc/language-reference/en/functions/time/delaymicroseconds/): la unidad µs tal como la usa la Mega (aparecerá en la Lección 43).

## Cuéntale a papá

Rétalo a un duelo de ritmos: quién aplaude más parejo a 2 Hz. Luego explícale con tus palabras por qué frecuencia y período son la misma idea al revés, y cuéntale el dato del día: el sensor de PX-32 trabaja a 40 000 Hz, con ciclos de solo 25 µs. Marca la casilla 40 en [PROGRESS.md](../../PROGRESS.md).

¿Qué hay más allá de los 20 000 Hz que tus oídos alcanzan a oír? En la [Lección 41](41-ultrasonido-mas-alla-del-oido.md) conocemos a los animales que viven ahí, y el grito silencioso de PX-32.
