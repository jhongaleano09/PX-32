# Lección 41 — Ultrasonido: más allá del oído

## El cazador que ve con los oídos

Cierra los ojos y trata de atrapar una mosca volando. Imposible. Ahora mira a un murciélago: vuela en una cueva completamente a oscuras, a toda velocidad, entre cientos de paredes y estalactitas… y no choca nunca. Tampoco la mosca escapa.

El truco del murciélago lo descubrió un científico italiano, Lazzaro Spallanzani, tapando los oídos de murciélagos con cera: chocaban contra todo. No era magia ni vista de rayos: **cazaban con el oído**. Gritan gritos agudísimos, muchísimo más agudos que cualquier sonido que tú puedas oír, y leen los ecos que rebotan de las polillas y las paredes. Con puro sonido construyen un mapa del mundo. A esa técnica los humanos la llamamos **ecolocación**, y hoy PX-32 va a empezar a aprenderla.

Ese territorio de sonidos demasiado agudos para nosotros tiene nombre: **ultrasonido**. Todo lo que vibra por encima de unos 20 000 Hz vive ahí. Tu oído termina ahí; el mundo del ultrasonido sigue mucho más allá, y está lleno de vecinos.

## Los vecinos del ultrasonido

- **Los perros** oyen bastante más arriba que las personas. Por eso el silbato para perros parece no sonar: tú oyes un soplo de aire y el perro, a veinte metros, levanta las orejas. El silbato está emitiendo en su zona ultrasónica.
- **Los murciélagos** gritan entre decenas y cientos de miles de hertz, según la especie.
- **Los delfines** ecolocan bajo el agua con clics ultrasonoros para encontrar peces en agua turbia.
- **El módulo de PX-32** (el tipo de sensor HC-SR04 que monta el robot) grita a **40 000 Hz**, el doble de lo más agudo que el oído humano joven puede captar. Cuando PX-32 "grita", tú oyes exactamente lo mismo que cuando calla: nada.

Una aclaración importante antes de seguir: **"no lo oigo" no significa "no existe" y tampoco significa "es inofensivo en cualquier cantidad"**. El silbato para perros es inofensivo, pero los sonidos —audibles o no— son energía que viaja; un ultrasonido potente, como el que usan las máquinas de limpieza industrial, puede hacer cosas muy reales. La regla de respetar el volumen vale para todo lo que vibra, lo oigas o no.

Y la palabra del día sale del murciélago y del robot a la vez: un **transductor** es cualquier pieza que transforma un tipo de energía en otra. En el sensor de PX-32 hay dos: uno convierte electricidad en empujones de aire (la voz) y el otro convierte los empujones que regresan en electricidad otra vez (el oído). El micrófono y el parlante de tu casa son transductores; los dos cilindros del sensor también.

## Lo que necesitas

- PX-32 en la mesa, apagado, **sin baterías y sin USB**.
- Buena luz para leer letras pequeñas en el frente del sensor.
- Tu cuaderno: hoy se arma una tabla para clasificar sonidos.
- Calculadora para convertir frecuencias a períodos (fórmula de la Lección 40).

🟢 Todo es observación y pizarra: no hay energía hoy.

## La actividad: el mapa del ultrasonido y el rostro de PX-32

1. 🟢 **Copia y completa la tabla** en el cuaderno. La primera fila va de ejemplo:

   | Sonido | Frecuencia aproximada | ¿Lo oyes? | ¿Es ultrasonido? |
   |---|---|---|---|
   | Trueno lejano | decenas de Hz | sí | no |
   | Tu voz hablando | entre unos 100 y 300 Hz | ___ | ___ |
   | Tecla más aguda de un piano | unos 4 000 Hz | ___ | ___ |
   | Tu límite auditivo | unos 20 000 Hz | apenas | ___ |
   | Silbato para perros | más de 20 000 Hz | ___ | ___ |
   | Grito del sensor de PX-32 | 40 000 Hz | ___ | ___ |
   | Grito de muchos murciélagos | hasta unos 200 000 Hz | ___ | ___ |

   La frontera del ultrasonido no es un muro exacto: cada oído tiene su propio límite y el de los adultos está más abajo que el de los niños. Por eso escribimos "aproximada": la física del sonido no cambia con tu oído, pero tu oído sí decide qué parte escuchas.

2. 🟢 **Calcula dos períodos** con `período = 1 / frecuencia`, en microsegundos: el de la tecla aguda del piano (4 000 Hz → 250 µs) y el del sensor (40 000 Hz → 25 µs; ya lo conoces de ayer). Fíjate: el doble de frecuencia, la mitad de período.

3. 🟢 **Encuentra los dos transductores.** Acércate al frente de PX-32 y mira la placa del sensor: son los **dos cilindros metálicos** que ubicaste en la Lección 39, montados sobre el soporte que gira. Busca junto a ellos (en la placa, en letra pequeña) las marcas **T** y **R**: **T** viene de *transmisor* (grita) y **R** de *receptor* (escucha). Cuidado con un parecido de nombres que confunde: el pin **Trig** de la fila de conexión (el que va a D30) es el cable de la orden, no un cilindro. Si tu módulo no tiene las letras visibles, no importa: los dos cilindros son idénticos a la vista, y su diferencia es a qué circuito están conectados por dentro. Anota: "el cilindro T grita, el cilindro R escucha, y Trig es un pin, no una pieza".

> **[PENDIENTE VISUAL]**
> - **Tipo:** fotografía anotada del módulo ultrasónico montado en PX-32.
> - **Objetivo:** que el niño identifique los dos transductores y los cuatro pines antes de programar el sensor.
> - **Descripción:** vista frontal del módulo con los dos cilindros metálicos resaltados y etiquetados T (grita) y R (escucha), y una segunda vista con los cuatro pines de conexión señalados: VCC, Trig, Echo y GND.
> - **Elementos que deben señalarse:** cilindro T, cilindro R, letras de serigrafía si son visibles, fila de 4 pines con sus nombres, soporte del servo detrás.
> - **Fuente técnica:** manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, página 29, esquema de conexión del módulo ultrasónico (imagen local: [página 29](../../assets/osoyoo-manual/pagina-29-conexion-ultrasonico.png)).
> - **Texto alternativo sugerido:** "Módulo ultrasónico con dos cilindros T y R señalados y sus cuatro pines de conexión etiquetados".

4. 🟢 **Comprueba el silencio del robot.** Pon tu oreja a un palmo del sensor (el robot sigue apagado; es para fijar la escena). Cuando PX-32 grite en unas lecciones más, desde este mismo lugar no oirás absolutamente nada: 40 000 Hz están 20 000 por encima de tu límite. Tu perro, si tienes, sí podría molestarse; por eso los sensores domésticos de este tipo se eligen para pasar desapercibidos.

5. 🟢 **La pregunta puente.** Anota tu predicción en el cuaderno: el sensor grita, el sonido viaja hasta una pared y regresa al cilindro R. ¿Qué cree el robot que necesita **medir** para saber a qué distancia está la pared: el volumen del grito, el color de la pared o el **tiempo** que tardó el viaje? Si respondiste "el tiempo", acabas de anticipar las próximas tres lecciones.

## Desafío: el traductor de murciélagos

Busca con tu padre un video de ecolocación de murciélagos (en la sección de lecturas hay material para empezar). Muchos videos "traducen" el grito bajándolo de frecuencia para que los humanos lo oigamos. Explica en tu cuaderno: si el grito real es de 80 000 Hz y el traductor lo convierte a 500 Hz para que lo oigas, ¿qué le pasó al período? (Pista: 1/80000 s = 12,5 µs reales; 1/500 s = 2 ms en la traducción. La traducción estira el tiempo 160 veces para que quepa en tu oído.)

## Si no funciona

| Síntoma | Qué revisar | Acción |
|---|---|---|
| No encuentro las letras T y R | ¿Miras la placa del sensor con buena luz? | Algunas versiones del módulo casi no las marcan; identifícalo por función (los dos cilindros idénticos) y sigue |
| La tabla me confunde | ¿Estás mezclando "frecuencia" con "volumen"? | Frecuencia es *cuántas veces por segundo* (agudo/grave); volumen es *qué tan fuerte* — dos cosas independientes |
| Dudo del dato de 40 000 Hz del módulo | ¿Consultaste el diccionario de hardware? | El manual de OSOYOO nombra el módulo genéricamente; los módulos tipo HC-SR04 trabajan a 40 kHz según su hoja de datos — cita ambas cosas en tu cuaderno, como hace el curso |
| El sensor de mi robot no está sobre un soporte giratorio | ¿Está montado directo sin servo? | Revisa el inventario de la Lección 02 con tu padre y anota la diferencia; el servo aparece en la Lección 47 |

## Lecturas y videos para explorar

- [Velocidad, frecuencia y longitud de onda del sonido](https://openstax.org/books/physics/pages/14-1-speed-of-sound-frequency-and-wavelength) — Inglés; libro abierto; 12 min. Aprenderás velocidad, frecuencia y longitud de onda del sonido. Esencial.
- [Biblioteca Servo](https://docs.arduino.cc/libraries/servo/) — Inglés; referencia oficial Arduino; 10 min. Aprenderás biblioteca servo. Opcional.

Pide a tu padre buscar "bat echolocation slowed down": escuchar un grito de murciélago estirado en el tiempo vale más que mil descripciones.

## Referencias técnicas de la clase

- [Hoja de datos del módulo HC-SR04 (SparkFun)](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf): frecuencia de trabajo de 40 kHz y protocolo Trig/Echo. El manual de OSOYOO nombra el módulo genéricamente como "Ultrasonic module" (ver [errata y estado de verificación](../../docs/hardware/HW-009-ultrasonico.md)).
- [HW-009 en el diccionario de hardware](../../docs/hardware/HW-009-ultrasonico.md): pines VCC/Trig/Echo/GND y estado de verificación.
- [OpenStax Physics, sección 14.1](https://openstax.org/books/physics/pages/14-1-speed-of-sound-frequency-and-wavelength): rango auditivo humano y ultrasonido.

## Cuéntale a papá

Cuéntale la historia de Spallanzani y los murciélagos con cera en los oídos, y muéstrale en PX-32 los dos cilindros que gritan y escuchan. Pregúntale si sabía que el silbato del perro de su infancia era ultrasonido. Y déjale una inquietud a propósito: si el robot mide distancias con tiempo de viaje, ¿de dónde sacará el sonido la velocidad para convertir tiempo en centímetros? Marca la casilla 41 en [PROGRESS.md](../../PROGRESS.md).

La respuesta es una velocidad con la que convives todos los días sin verla: en la [Lección 42](42-eco-y-tiempo-de-vuelo.md) la cacemos con un trueno.
