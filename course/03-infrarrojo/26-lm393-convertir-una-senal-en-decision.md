# Lección 26 — LM393: convertir una señal en decisión

## El árbitro que solo sabe decir sí o no

El receptor del sensor entrega un voltaje que cambia poco a poco con la cantidad de luz que regresa: mucha luz con el cartón blanco cerca, menos si lo alejas, casi nada con el paño negro. Es una señal **analógica**: puede tomar muchos valores intermedios, como la manija del volumen de un equipo de sonido.

Pero el pin OUT del módulo no entrega una escala: entrega dos estados, nada más. Entre la escala suave y la respuesta de dos estados hay un personaje que decide, y es el chip negro de muchas patas que identificaste en la Lección 24: el **LM393**, un **comparador** de voltajes.

Imagina un árbitro de boxeo que solo mira dos tarjetas de puntaje y anuncia quién va ganando. No le importa por cuánto: no explica, no gradúa, solo señala un ganador. El LM393 hace eso con dos voltajes. En una entrada recibe la señal del receptor; en la otra recibe un voltaje de referencia llamado **umbral**. Su salida digital declara cuál de los dos es mayor. Si la señal del receptor cruza el umbral, la salida cambia de estado: el LED de señal se enciende y el pin OUT cambia de valor.

Ese corte convierte una rampa en un escalón:

```text
señal del receptor
  |          ____/
  |      ___/
  |  ___/            <- la señal cambia poco a poco
  |____________________  distancia al objeto

salida del LM393
  |
  |  ------------+--------
  |               |          <- la salida salta de golpe
  |_______________|
  |____________________  distancia al objeto
```

La conversión es útil porque la Mega lee decisiones mucho más fácil que escalas, pero cuesta algo: se pierde información. La salida ya no dice cuánta luz regresó, solo si fue suficiente. Por eso el sensor no mide distancias en centímetros: en la Lección 25 viste que "suficiente luz" depende del material, no solo de la distancia.

Hay una consecuencia más, y es la estrella del experimento de hoy: justo en la frontera, la salida puede titubear. Si la señal anda rondando el umbral, cualquier cosita —el temblor de tu mano, un cambio pequeño de luz ambiente— la empuja para un lado o para el otro, y el LED parpadea. A eso lo llamaremos la **zona inestable**, y la vamos a conocer bien, porque cuando el robot tome decisiones de movimiento tendremos que respetarla.

## Lo que necesitas

- PX-32 con sus sensores conectados y montados.
- El rectángulo de cartón blanco de la Lección 25.
- Una regla.
- Tu cuaderno y lápiz.
- Cable USB, computador y un adulto para energizar.

Estado inicial: robot apagado, sin baterías, sobre la mesa. No habrá movimiento en toda la clase.

🟡 El adulto conecta el USB al inicio y lo retira al final. La única energía es la del cable.

## Encuentra el punto de cambio… y la zona que tiembla

1. 🟡 **Energiza.** El adulto conecta el USB. LED de alimentación encendido en ambos sensores.

2. 🟢 **Aproxímate por centímetros.** Frente al sensor izquierdo, sostén el cartón blanco a 30 cm y acércalo de a un centímetro, marcando cada paso con la regla. Anota la distancia exacta donde el LED de señal se enciende por primera vez: ese es tu **punto de cambio**, la distancia a la que la señal cruza el umbral.

3. 🟢 **Regresa.** Ahora aléjalo con el mismo cuidado. ¿Se apaga a la misma distancia donde se encendió? Anota ambas; suelen estar muy cerca, pero no siempre idénticas.

4. 🟢 **Caza la zona inestable.** Quédate en la frontera: a un centímetro antes y después del punto de cambio, mueve el cartón milímetro a milímetro. Observa el LED: en algún tramo parpadeará o se encenderá y apagará sin un motivo visible. No está roto: la señal está rondando el umbral y el árbitro cambia de veredicto con cada empujoncito. Dibuja en tu cuaderno una recta con el punto de cambio marcado y la zona inestable rayada alrededor.

5. 🟢 **Provoca y calma la frontera.** Con el cartón quieto en la frontera, acerca y aleja tu otra mano por un costado, hacia la lámpara de la sala: a veces el ruido de luz ambiente basta para voltear el veredicto. Apaga la lámpara y observa si el LED se estabiliza. El umbral no se movió; se movió el piso del cual parte la señal.

6. 🟢 **Compara el sensor derecho.** Repite los pasos 2 y 3 con el otro sensor. Con casi total seguridad, su punto de cambio no está a la misma distancia: cada módulo tiene su propio receptor, su propio LM393 y su propio umbral de fábrica. Anota ambos números: "izquierdo enciende a __ cm, derecho a __ cm". Esa diferencia es la materia prima de la Lección 27.

7. 🟢 **Dibuja tu gráfica.** En el cuaderno, traza dos ejes: horizontal la distancia al cartón, vertical un valor inventado de "luz que regresa". Dibuja la rampa descendente a medida que el cartón se aleja, el umbral como una línea horizontal, el punto donde se cruzan y la zona inestable sombreada alrededor del cruce.

8. 🟡 **Cierre.** El adulto retira el USB.

La clase está completa cuando tienes tres cosas en el cuaderno: el punto de cambio de cada sensor, la zona inestable dibujada, y una explicación tuya de qué información se pierde al convertir la rampa en escalón.

> **[PENDIENTE VISUAL]**
> - **Tipo:** gráfica comparativa señal analógica contra salida digital.
> - **Objetivo:** entender visualmente la función del comparador y la zona inestable cerca del umbral.
> - **Descripción:** gráfica con la distancia al objeto en el eje horizontal; una curva suave que baja (luz que regresa) cruzada por una línea horizontal punteada (umbral); debajo, una segunda gráfica con la salida digital saltando de un nivel a otro justo en el cruce, con una franja sombreada de parpadeo alrededor.
> - **Elementos que deben señalarse:** curva de señal, línea de umbral, punto de cambio, zona inestable, niveles alto y bajo de la salida.
> - **Fuente técnica:** hoja de datos del LM393 de Texas Instruments, https://www.ti.com/lit/ds/symlink/lm193.pdf, comparador diferencial con salida de colector abierto.
> - **Texto alternativo sugerido:** "Dos gráficas muestran una señal que baja suavemente y una salida digital que salta al cruzar el umbral, con una zona de parpadeo en la frontera".

## Desafío: el termómetro de Herschel moderno

Herschel descubrió el infrarrojo midiendo su efecto con un termómetro. Tu "termómetro" es el LED de señal. Diseña una prueba que responda: ¿la zona inestable se hace más ancha o más angosta con la lámpara de la sala encendida? Recuerda cambiar una sola condición y escribir tu predicción antes de medir.

## Si algo no cuadra

| Síntoma | Qué revisar | Acción |
|---|---|---|
| El LED nunca cambia de estado | ¿El cartón es blanco y empiezas a 30 cm? | Empieza más cerca; si tampoco, el umbral quedó muy exigente: Lección 27 |
| El LED está siempre encendido | ¿Hay algo frente al sensor o luz muy directa? | Despeja el frente; si persiste, es el síntoma clásico de umbral demasiado sensible |
| No encuentro la zona inestable | ¿Te mueves por pasos muy grandes? | Trabaja milímetro a milímetro justo en la frontera |
| El punto de cambio cambia entre intentos | ¿La luz ambiente o tu ángulo cambiaron? | Controla las condiciones y anótalas junto a cada dato |

## Lecturas y videos para explorar

- [El espectro electromagnético y el infrarrojo](https://science.nasa.gov/ems/07_infraredwaves/) — Inglés; lectura NASA; 8 min. Aprenderás el espectro electromagnético y el infrarrojo. Esencial.
- [Sensores de PX-32](../../docs/reference/sensores.md) — Español; referencia interna; 6 min. Aprenderás sensores de px-32. Opcional.

La referencia interna insiste en distinguir la medición de la interpretación: hoy viste exactamente dónde nace esa distinción, en el corte del comparador.

## Referencias técnicas de la clase

- [Hoja de datos LM393 de Texas Instruments](https://www.ti.com/lit/ds/symlink/lm193.pdf), familia de comparadores diferenciales duales con salida de colector abierto.
- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), páginas 39 a 43, papel del indicador de señal en la detección.
- [Glosario de PX-32](../../docs/reference/glosario.md), entradas comparador, analógico y digital.

## Cuéntale a papá

Explícale el trabajo del árbitro con las dos tarjetas de puntaje y por qué la salida ya no sabe "cuánta" luz regresó, solo "si fue suficiente". Muéstrale tu gráfica de la rampa y el escalón y cuéntale qué pasa en la zona que tiembla. Para terminar, pregúntale dónde usa la vida cotidiana decisiones de solo dos estados (pistas: el timbre de la puerta, la alarma del carro, el cinturón de seguridad puesto o no).

Cada sensor tiene su propio punto de cambio, y no coinciden. En la [Lección 27](27-el-potenciometro-ajusta-el-umbral.md) usarás el tornillo azul para ponerlos de acuerdo a una distancia exacta de trabajo.
