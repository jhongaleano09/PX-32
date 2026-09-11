# Lección 25 — Reflexión y absorción

## Por qué la camiseta negra quema en el verano

Dos camisetas al sol, misma hora, misma piel: la blanca se siente tibia y la negra quema. La luz que les llega es la misma; lo que cambia es qué hacen con ella. La blanca **refleja** gran parte de la luz: la devuelve al mundo y se queda poca energía. La negra **absorbe**: se queda con la energía y se calienta.

Lo mismo les pasa a los objetos frente al sensor de PX-32, y aquí está el truco que hay que entender bien: el sensor no pregunta "¿qué tan lejos está el objeto?". Pregunta "¿regresó suficiente luz a mi receptor?". Y la respuesta depende del material, de la distancia y hasta del ángulo. Un cartón blanco a 20 cm puede devolver más luz que un paño negro a 8 cm. Un sensor infrarrojo de reflexión no mide distancias: mide cuánta luz regresó.

Hay un detalle más, y es delicioso: no todos los objetos brillantes reflejan igual. El papel blanco es mate: rebate la luz en todas direcciones, como una pared pintada. El papel aluminio es como un espejo: rebate la luz en una sola dirección, ordenada. Si inclinas el aluminio, el reflejo se marcha para otro lado y el sensor "pierde" un objeto que estaba justo enfrente, aunque sea lo más brillante de la mesa. A la reflexión mate se le llama difusa; a la de espejo, especular.

Todo esto lo vas a medir con tu propio sensor, y la moneda del experimento será el LED de señal que conociste en la Lección 24: encendido significa "regresó suficiente luz"; apagado, "no regresó la suficiente". Guárdate esta idea para el futuro cercano: el seguimiento de línea del próximo bloque funciona exactamente así, con una cinta negra que absorbe y un piso blanco que refleja.

## Lo que necesitas

- PX-32 con sus dos sensores conectados según el mapa.
- Un rectángulo de cartón o papel blanco (media carta está bien).
- Un rectángulo de cartón o fieltro negro.
- Un trozo de papel aluminio (puedes pegarlo plano sobre un cartón para que quede firme).
- Una prenda o tela oscura.
- Una regla o cinta métrica.
- Tu cuaderno con una tabla como la de abajo.
- Cable USB, computador y un adulto para energizar.

Estado inicial: PX-32 apagado y sin baterías sobre la mesa, quieto. Los sensores deben estar calibrados de fábrica o al menos encender su LED de alimentación con USB.

🟡 El adulto conecta el USB y permanece cerca. No habrá movimiento: la única energía de la clase es la del cable.

## La tabla de materiales

| Material | ¿Detecta a 10 cm? (3 pruebas) | Distancia máxima aproximada |
|---|---|---|
| Cartón blanco | | |
| Cartón negro | | |
| Papel aluminio | | |
| Tela oscura | | |
| Tu mano | | |

1. 🟢 **Predice el orden.** Antes de probar nada, ordena en el cuaderno los cinco materiales del que crees que se detectará más lejos al que se detectará más cerca. Tu predicción queda congelada antes del primer dato.

2. 🟡 **Energiza.** El adulto conecta el USB. Verifica que el LED de alimentación de ambos sensores esté encendido.

3. 🟢 **Prueba a 10 cm, tres veces cada material.** Elige un sensor y úsalo durante toda la tabla; para no confundirte de lado, recuerda que el izquierdo es el cuyo cable de tres hilos llega a D3. Sostén cada material plano, frente a las cápsulas, a 10 cm medidos con la regla. Mantén el mismo ángulo (paralelo al sensor) y la misma mano que sostiene. Anota "sí" o "no" tres veces por material; si sale distinto entre intentos, anótalo también: ese dato vale.

4. 🟢 **Mide la distancia máxima.** Con el cartón blanco empieza a 10 cm y aléjalo despacio, milímetro a milímetro, hasta que el LED de señal se apaga. Anota esa distancia. Repite la medición con el aluminio y con tu mano. Con los materiales oscuros, mide también: tal vez la respuesta sea "no detecta ni a 5 cm", y eso también es un dato.

5. 🟢 **El truco del espejo.** Vuelve a poner el aluminio a 10 cm, detectándose. Ahora inclínalo unos 30 grados, como un espejo que desvía el sol. El LED puede apagarse aunque el aluminio siga brillante y cercano: el reflejo especular se fue a otra parte y no regresó al ojo del sensor. Compara con el cartón blanco inclinado igual: al ser difuso, sigue devolviendo algo de luz en muchas direcciones. Anota la diferencia.

6. 🟢 **Cambia una sola condición: la luz de la sala.** Elige el cartón blanco a una distancia donde se detecte, y repite la medición con la lámpara principal de la habitación encendida y apagada. Si el resultado cambia, acabas de conocer al ruido de la Lección 24 en acción: el infrarrojo ambiente altera la lectura. Anota las condiciones junto al dato.

7. 🟢 **Cierra la tabla.** Compara tu orden final con tu predicción del paso 1 y explica las diferencias con las palabras reflexión, absorción, difusa y especular.

8. 🟡 **Cierre.** El adulto retira el USB.

La actividad está completa cuando tu tabla tiene al menos los cinco materiales probados a 10 cm con tres repeticiones, dos distancias máximas medidas, y una frase tuya que explique por qué el mismo sensor "ve" distinto según el material.

> **[PENDIENTE VISUAL]**
> - **Tipo:** diagrama de tres paneles sobre reflexión.
> - **Objetivo:** distinguir visualmente reflexión difusa, especular y absorción frente al sensor.
> - **Descripción:** tres viñetas con el módulo sensor a la izquierda emitiendo un haz hacia un material: en la primera, un cartón blanco rebate flechas en muchas direcciones y una regresa al receptor; en la segunda, el aluminio rebate una sola flecha ordenada que se va lejos del receptor; en la tercera, el paño negro se "come" el haz con una marca de calor y casi nada regresa.
> - **Elementos que deben señalarse:** haz infrarrojo de ida, flechas de regreso, receptor, rótulos difusa/especular/absorción.
> - **Fuente técnica:** NASA Science, https://science.nasa.gov/ems/08_nearinfraredwaves/, reflexión del infrarrojo cercano según superficie.
> - **Texto alternativo sugerido:** "Tres diagramas muestran cómo un cartón blanco refleja en todas direcciones, el aluminio refleja como espejo y el paño negro absorbe el haz infrarrojo".

## Desafío: el detective de materiales

Sin que tú mires, pide al adulto que escoja un objeto de la casa y te diga solo dos datos: a qué distancia máxima lo detecta el sensor y de qué color es. Con esa información, adivina si su superficie es mate o brillante, y explica tu razonamiento. Luego compruébalo con el objeto.

## Si algo no cuadra

| Síntoma | Qué revisar | Acción |
|---|---|---|
| Todo se detecta igual, hasta el negro a 30 cm | ¿El umbral quedó muy sensible? | Anótalo: lo ajustarás en la Lección 27; por ahora registra los datos relativos entre materiales |
| Nada se detecta, ni la mano a 5 cm | ¿El LED de alimentación está encendido? | Verifica energía; si está encendido, el umbral quedó muy exigente (Lección 27) |
| Las tres pruebas del mismo material dan distinto | ¿Distancia, ángulo o luz cambiaron entre intentos? | Controla una variable a la vez y registra las condiciones |
| El aluminio inclinado sigue detectándose | ¿El ángulo fue pequeño o el sensor recibe reflejos de la mesa? | Inclina un poco más o cambia el sensor de lugar sobre la mesa |

## Lecturas y videos para explorar

- [El espectro electromagnético y el infrarrojo](https://science.nasa.gov/ems/07_infraredwaves/) — Inglés; lectura NASA; 8 min. Aprenderás el espectro electromagnético y el infrarrojo. Esencial.
- [Sensores de PX-32](../../docs/reference/sensores.md) — Español; referencia interna; 6 min. Aprenderás sensores de px-32. Opcional.

Después de tu tabla, la página de NASA te mostrará fotos de vegetación en infrarrojo cercano: la misma física de reflexión que mediste, usada para estudiar plantas desde aviones y satélites.

## Referencias técnicas de la clase

- [NASA Science: infrarrojo cercano reflejado](https://science.nasa.gov/ems/08_nearinfraredwaves/), cómo el material y el color cambian la reflexión del infrarrojo cercano.
- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), páginas 39 a 43, comportamiento de los sensores IR con objetos a distintas distancias.
- [Ficha HW-008 del repositorio](../../docs/hardware/HW-008-ir-obstaculos.md), experimento mínimo con superficies de distinto material.

## Cuéntale a papá

Muéstrale la tabla terminada y explícale por qué el negro no "aparece" para el sensor aunque esté cerca. Cuéntale lo del aluminio inclinado y pregúntale dónde ha visto ese efecto con luz visible (pistas: un espejo de carro, el destello de un reloj, un charco al sol). Cierra explicando por qué el próximo robot seguidor de líneas necesitará una línea negra sobre piso blanco.

Ya sabes que la cantidad de luz que regresa es gradual: mucha con el blanco, poquísima con el negro. Pero el sensor solo contesta sí o no. En la [Lección 26](26-lm393-convertir-una-senal-en-decision.md) conocerás al árbitro que corta esa escala gradual en dos.
